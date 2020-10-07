/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:42:20 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/07 09:44:57 by akovalyo         ###   ########.fr       */
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
** Returns pointer to the value of the environment variable 'var' if found,
** else NULL
*/

char	*get_envv(char *var)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_straddchr(var, '=');
	while (g_sh.env[i])
	{
		if (ft_strncmp(g_sh.env[i], tmp, ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (ft_strchr(g_sh.env[i], '=') + 1);
		}
		i++;
	}
	free(tmp);
	print_error("failed to load env variable", 1);
	return (NULL);
}

/*
** Returns index of the environment variable 'var' if found, else -1
*/

int		get_envv_pos(char *var)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_straddchr(var, '=');
	while (g_sh.env[i])
	{
		if (ft_strncmp(g_sh.env[i], tmp, ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (i);
		}
		i++;
	}
	free(tmp);
	return (-1);
}

/*
** Replaces value of the variable 'var' with the 'value' in the environment var.
** If 'var' not found, adds it.
*/

void	change_envv(char *var, char *value)
{
	int		pos;
	char	*tmp;
	char	*new;

	if ((pos = get_envv_pos(var)) < 0)
		return (add_envv(var, value));
	tmp = g_sh.env[pos];
	new = ft_straddchr(var, '=');
	new = ft_strjoin_free(new, value);
	g_sh.env[pos] = ft_strdup(new);
	free(new);
	free(tmp);
}

/*
** Adds value to the environment variable.
*/

void	add_envv(char *var, char *value)
{
	char *new;

	new = ft_straddchr(var, '=');
	new = ft_strjoin_free(new, value);
	g_sh.env = add_elem_to_arr(g_sh.env, new, free);
}
