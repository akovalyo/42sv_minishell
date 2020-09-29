/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:24:09 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/28 17:06:07 by akovalyo         ###   ########.fr       */
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


void 	parser(char *str)
{
	int i;
	char *arg;

	i = 0;
	arg = NULL;
	i = skip_spaces(str, i);
	if (str[i])
		arg = get_first_arg(str, &i);
	if (!arg)
		return ;
	addnode_comm(arg);
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i = addnode_spaces(str, i);
		else if (str[i] == '-' && !g_sh.fl_ignore)
			i = addnode_flags(str, i);
		else if (str[i] == '$')
			i = addnode_envv(str, i);
		else if (str[i] == '~')
			i = addnode_tilde(str, i);
		else if (special_char(str[i]))
			i = addnode_specialch(str, i);
		else
			i = addnode_str(str, i);
	}
	free(arg);
}