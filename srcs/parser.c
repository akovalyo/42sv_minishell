/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:24:09 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/01 14:55:26 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		skip_spaces(char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

char *get_first_arg(char *str, int *i)
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



void	add_to_map(t_list *new)
{
	t_list **tmp;
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
		i = 0;
		size = ft_arraylen((void **)g_sh.map) + 2;
		tmp = g_sh.map;
		g_sh.map = malloc(sizeof(t_list **) * size);
		g_sh.map[size - 1] = NULL;
		while (i < size - 2)
		{
			g_sh.map[i] = tmp[i];
			i++;
		}
		g_sh.map[i] = new;
		free(tmp);
	}
}

// void parser_rest(char *str, int i)
// {
// 	while (str[i])
// 	{
// 		if (ft_isspace(str[i]))
// 			i = addnode_spaces(str, i);
// 		else if (str[i] == '-' && !g_sh.fl_ignore)
// 			i = addnode_flags(str, i);
// 		else if (str[i] == '$')
// 			i = addnode_envv(str, i);
// 		else if (str[i] == '~')
// 			i = addnode_tilde(str, i);
// 		else if (special_char(str[i]))
// 			i = addnode_specialch(str, i);
// 		else
// 			i = addnode_str(str, i);
// 	}
// }


void 	parser(char *str)
{
	int i;
	//char *arg;

	i = 0;
	//arg = NULL;
	//i = skip_spaces(str, i);
	// if (!(ft_strlen(&str[i])))
	// 	return ;
	while (str[i])
	{
		if (!g_sh.tokens || (str[i] == '|' && g_sh.n_comm > 0))
			i = addnode_comm(str, i);
		else if (ft_isspace(str[i]))
			i = addnode_spaces(str, i);
		else if (str[i] == '-' && !g_sh.fl_ignore)
			i = addnode_flags(str, i);
		else if (str[i] == '$')
			i = addnode_envv(str, i);
		else if (str[i] == '~')
			i = addnode_tilde(str, i);
		else if (isredir(str[i]) && ((g_sh.sn_qt % 2) == 0 || (g_sh.db_qt % 2) == 0))
			i = addnode_redir(str, i);
		else if (special_char(str[i]))
			i = addnode_specialch(str, i);
		else
			i = addnode_str(str, i);
	
	}
	//ft_printf("%d-%s\n", ft_arraylen((void **)g_sh.map), g_sh.map[0]->content);
	
	//free(arg);
}