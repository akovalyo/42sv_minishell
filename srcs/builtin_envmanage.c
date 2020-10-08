/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_envmanage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:00:17 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/07 18:53:29 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks if argument is correct, then add get key and value 
*/

void	get_key_value(char *arg, char **key, char **value)
{
	int i;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=' && !ft_isspace(arg[i]))
		i++;
	if (!arg[i] || ft_isspace(arg[i]))
		return ;
	*key = ft_strsub(arg, 0, i);
	*value = ft_strdup(&arg[i + 1]);
}

/*
** Executes the builtin export command
*/

void		comm_export(char **argv)
{
	int		argc;
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	argc = ft_arraylen((void **)argv);
	if (argc == 1)
		ft_strarr_print(g_sh.env);
	else
	{
		get_key_value(argv[1], &key, &value);
		if (!key || !value)
			return (print_error("usage: export KEY=value", 1));
		change_envv(key, value);
		free(key);
		free(value);
	}
}

/*
**	Executes the builtin unset command
*/

void		comm_unset(char **argv)
{
	int		i;
	int		env_ind;

	i = 0;
	if (ft_arraylen((void **)argv) == 2)
	{
		while (argv[1][i] != '\0' && !ft_isspace(argv[1][i]))
			i++;
		if (ft_isspace(argv[1][i]))
			return ;
		if ((env_ind = get_envv_pos(argv[1])) >= 0)
		{
			free(g_sh.env[env_ind]);
			g_sh.env[env_ind] = NULL;
		}
	}
	else
		return (print_error("usage: unset KEY", 1));
}
