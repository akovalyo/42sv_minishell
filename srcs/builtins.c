/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:15:50 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/07 15:44:30 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Executes the builtin echo command
*/

void	comm_echo(char **arg)
{
	int		i;
	int		len;

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

/*
** Executes the builtin pwd command
*/

void	comm_pwd(char **arg)
{
	int		arg_len;

	arg_len = ft_arraylen((void **)arg);
	if (arg_len == 1)
		ft_printf("%s\n", get_pwd());
	else
		print_error("too many arguments", 1);
}

/*
** Prints the environment variable
*/

void	comm_env(char **arg)
{
	int		i;

	i = -1;
	if (ft_arraylen((void **)arg) == 1)
	{
		while (g_sh.env[++i])
			ft_printf("%s\n", g_sh.env[i]);
	}
	else
		print_error("too many arguments", 1);
}
