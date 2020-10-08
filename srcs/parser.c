/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:24:09 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/07 23:14:39 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Skips spaces in the string and returns the next index.
*/

int		skip_spaces(char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

/*
** Returns the first argument
*/

char 	*get_first_arg(char *str, int *i)
{
	char *arg;
	int start;

	arg = NULL;
	start = *i;
	while (str[*i] && !ft_isspace(str[*i]))
		(*i)++;
	if (start - *i == 0)
		return (NULL);
	arg = ft_strsub(str, start, *i - start);
	check_builtins_and_bin(arg);
	return (arg);
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

void 	parser(char *str)
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
			i = addtoken_status(str, i);
		else if (str[i] == '$')
			i = addtoken_envv(str, i);
		else if (str[i] == '~')
			i = addtoken_tilde(str, i);
		else if (isredir(str[i]) && ((g_sh.sn_qt % 2) == 0 || (g_sh.db_qt % 2) == 0))
			i = addtoken_redir(str, i);
		else if (special_char(str[i]))
			i = addtoken_specialch(str, i);
		else
			i = addtoken_str(str, i);
	}
}
