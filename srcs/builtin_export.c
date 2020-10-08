/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:00:17 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/07 17:56:35 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks if argument is correct, then add key=value to 
** the environment variable.
*/

void	exec_export(char *arg)
{
	char *key;
	char *value;
	int i;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=' && !ft_isspace(arg[i]))
		i++;
	if (!arg[i] || ft_isspace(arg[i]))
		return (print_error("usage: export KEY=value", 1));
	key = ft_strsub(arg, 0, i);
	value = ft_strdup(&arg[i + 1]);
	change_envv(key, value);
	free(key);
	free(value);
}

/*
** Executes the builtin export command
*/

void		comm_export(char **argv)
{
	int		arg_len;

	arg_len = ft_arraylen((void **)argv);
	if (arg_len == 1)
		ft_strarr_print(g_sh.env);
	else
		exec_export(argv[1]);
}
