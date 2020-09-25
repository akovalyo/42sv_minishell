/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:24:09 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/25 16:26:05 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		parser(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (ft_isspace(arg[i]))
			i = addnode_spaces(arg, i);
		else if (arg[i] == '-' && !g_sh.fl_ignore)
			i = addnode_flags(arg, i);
		else if (arg[i] == '$')
			i = addnode_envv(arg, i);
		else if (arg[i] == '~')
			i = addnode_tilde(arg, i);
		else if (special_char(arg[i]))
			i = addnode_specialch(arg, i);
		else
			i = addnode_str(arg, i);
	}
}