/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_envmanage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:00:17 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/16 14:50:27 by akovalyo         ###   ########.fr       */
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
	{
		*key = ft_strsub(arg, 0, i);
		return ;
	}
	*key = ft_strsub(arg, 0, i);
	*value = ft_strdup(&arg[i + 1]);
}

/*
** Prints environment variabels
*/

void	declare_env(void)
{
	int i;

	i = -1;
	while (g_sh.env[++i])
		ft_printf("declare -x %s\n", g_sh.env[i]);
}

/*
** Executes the builtin export command
*/

void	comm_export(char **argv)
{
	int		argc;
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	argc = ft_arraylen((void **)argv);
	if (argc == 1)
		declare_env();
	else
	{
		get_key_value(argv[1], &key, &value);
		if (key && !value)
			change_envv(key, "", NULL);
		change_envv(key, value, NULL);
		free(key);
		free(value);
	}
}

/*
**	Executes the builtin unset command
*/

void	comm_unset(char **argv)
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
			g_sh.env = remove_envv(env_ind);
	}
	else
		return (print_error("usage: unset KEY", 1));
}
