/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:15:50 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/07 18:36:09 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Executes the builtin echo command
*/

void	comm_echo(char **argv)
{
	int		i;
	int		argc;

	i = 1;
	argc = ft_arraylen((void **)argv);
	if (argc == 1)
		ft_printf("\n");
	else
	{
		if (ft_strncmp(argv[1], "-n", 3) == 0)
			i++;
		while (i < argc)
		{
			ft_printf("%s", argv[i]);
			i++;
		}
		if (ft_strncmp(argv[1], "-n", 3) != 0)
			ft_printf("\n");
	}
}

/*
** Executes the builtin pwd command
*/

void	comm_pwd(char **argv)
{
	int		argc;

	argc = ft_arraylen((void **)argv);
	if (argc > 1)
		return (print_error("too many arguments", 1));
	ft_printf("%s\n", get_pwd());	
}

/*
** Prints the environment variable
*/

void	comm_env(char **argv)
{
	int		i;

	i = -1;
	if (ft_arraylen((void **)argv) > 1)
		return	(print_error("too many arguments", 1));
	ft_strarr_print(g_sh.env);	
}
