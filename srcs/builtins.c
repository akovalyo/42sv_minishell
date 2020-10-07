/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:15:50 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/05 16:37:17 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		comm_echo(char **arg, int map_i)
{
	int i;
	int len;

	i = 1;
	len = ft_arraylen((void **)arg);

	if (len == 1)
		ft_printf("\n");
	else
	{
		if (ft_strncmp(arg[1], "-n", 3) == 0)
			i++;
		while (i < len)
		{
			ft_printf("%s", arg[i]);
			i++;
		}
		if (ft_strncmp(arg[1], "-n", 3) != 0)
			ft_printf("\n");

	}
}

void		comm_pwd(char **arg, int map_i)
{
	int arg_len;

	arg_len = ft_arraylen((void **)arg);
	if (arg_len == 1)
		ft_printf("%s\n", get_pwd());
	else
		print_error("too many arguments", 1);	
}