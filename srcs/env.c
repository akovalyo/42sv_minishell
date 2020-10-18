/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:42:20 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/18 13:54:31 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
** Replaces value of the variable 'key' with the 'value' in the environment var.
** If 'key' not found, adds it.
*/

void	change_envv(char *key, char *value, void (*del)(void *))
{
	int		pos;
	char	*tmp;
	char	*new;

	if ((pos = get_envv_pos(key)) < 0)
		return (add_envv(key, value));
	tmp = g_sh.env[pos];
	new = ft_straddchr(key, '=');
	new = ft_strjoin_free(new, value);
	g_sh.env[pos] = ft_strdup(new);
	if (del)
		free(value);
	free(new);
	free(tmp);
}

/*
** Adds value to the environment variable.
*/

void	add_envv(char *key, char *value)
{
	char *new;

	new = ft_straddchr(key, '=');
	new = ft_strjoin_free(new, value);
	g_sh.env = add_elem_to_arr(g_sh.env, new, free);
}

/*
** Removes a variable in the position 'pos' from the environment
** variable.
*/

char	**remove_envv(int pos)
{
	char	**new_env;
	int		size;
	int		i;
	int		j;

	size = ft_arraylen((void **)g_sh.env);
	i = -1;
	j = 0;
	if (!(new_env = (char **)malloc(sizeof(char *) * size)))
	{
		print_error(strerror(errno), errno);
		return (NULL);
	}
	while (++i < size)
	{
		if (i == pos)
			continue ;
		new_env[j] = ft_strdup(g_sh.env[i]);
		j++;
	}
	new_env[j] = NULL;
	ft_strarr_free(g_sh.env);
	return (new_env);
}
