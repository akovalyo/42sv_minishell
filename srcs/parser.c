/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:24:09 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/13 17:05:15 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Process the list of tokens between quotes and return combined string.
*/

char	*between_quotes(char *str, t_list **lstptr)
{
	char	*tmp;
	t_ctg	qt;

	qt = (*lstptr)->ctg;
	*lstptr = (*lstptr)->next;
	while (*lstptr && (*lstptr)->ctg != qt)
	{
		if ((*lstptr)->ctg == SP)
		{
			while ((*lstptr)->atr-- > 0)
				str = ft_straddchr_free(str, ' ');
		}
		else
		{
			tmp = str;
			str = ft_strjoin(str, (*lstptr)->content);
			free(tmp);
		}
		*lstptr = (*lstptr)->next;
	}
	g_sh.flag = 0;
	return (str);
}

/*
** Checks the user input for ';', if it is separator or character.
*/

void	process_semicolons(char **str)
{
	int i;
	char qt;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
		{
			qt = (*str)[i];
			i++;
			while ((*str)[i] && (*str)[i] != qt)
				i++;
		}	
		if ((*str)[i] == ';')
			(*str)[i] = 7;
		if ((*str)[i] != '\0')
			i++;
	}
}

/*
** Reads input from user, splits it into separate command lines.
*/

char	**read_input(void)
{
	char	**tab_input;
	int		ret;
	char	*buff;

	buff = NULL;
	ret = get_next_line(0, &(g_sh.input));
	if (!ret && !ft_strlen(g_sh.input))
		exit_shell(errno);
	while (ret == 0)
	{
		ret = get_next_line(0, &buff);
		if (ret == 0)
			free(buff);
	}
	if (buff)
	{
		g_sh.input = ft_strjoin_free(g_sh.input, buff);
		free(buff);
	}
	process_semicolons(&(g_sh.input));
	tab_input = ft_strsplit(g_sh.input, 7);
	free(g_sh.input);
	g_sh.input = NULL;
	return (tab_input);
}

/*
** Saves address pointed to the token node in the array g_sh.map
*/

void	add_to_map(t_list *new)
{
	t_list	**tmp;
	int		size;
	int		i;

	if (!g_sh.map)
	{
		g_sh.map = malloc(sizeof(t_list *) * 2);
		g_sh.map[1] = NULL;
		g_sh.map[0] = new;
	}
	else
	{
		i = -1;
		size = ft_arraylen((void **)g_sh.map) + 2;
		tmp = g_sh.map;
		g_sh.map = malloc(sizeof(t_list **) * size);
		g_sh.map[size - 1] = NULL;
		while (++i < size - 2)
			g_sh.map[i] = tmp[i];
		g_sh.map[i] = new;
		free(tmp);
	}
}

/*
** Parses the command line from the command's queue, creates nodes
** and adds them to the token list
*/

void	parser(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!g_sh.tokens || (str[i] == '|' && g_sh.n_comm > 0))
			i = addtoken_comm(str, i);
		else if (ft_isspace(str[i]))
			i = addtoken_spaces(str, i);
		else if (str[i] == '-' && !g_sh.fl_ignore)
			i = addtoken_flags(str, i);
		else if (ft_strncmp(&str[i], "$?", 2) == 0)
			i = addtoken_status(i);
		else if (str[i] == '$')
			i = addtoken_envv(str, i);
		else if (str[i] == '~')
			i = addtoken_tilde(str, i);
		else if (isredir(str[i]) && ((g_sh.sn_qt % 2) == 0 ||
				(g_sh.db_qt % 2) == 0))
			i = addtoken_redir(str, i);
		else if (special_char(str[i]))
			i = addtoken_specialch(str, i);
		else
			i = addtoken_str(str, i);
	}
}
