/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:42:20 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/30 14:46:48 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Copies the environment variable of the parent shell to the g.sh
*/

void	init_env(char **env)
{
	int i;

	i = 0;
	g_sh.env = ft_memalloc(sizeof(char *) * (ft_arraylen((void **)env) + 1));
	while (env[i])
	{
		
		if (!(g_sh.env[i] = ft_strdup(env[i])))
			exit_shell(errno);
		i++;
	}
}

/*
** Returns pointer to the value of the environment variable 'var' if found, else NULL
*/

char		*get_env(char *var)
{
	int i;

	i = 0;
	while (g_sh.env[i])
	{
		if (ft_strncmp(g_sh.env[i], var, ft_strlen(var)) == 0)
			return (ft_strchr(g_sh.env[i], '=') + 1);
		i++;
	}
	return (NULL);
}