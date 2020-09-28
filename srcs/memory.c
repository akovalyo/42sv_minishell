/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:11:13 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/28 11:36:00 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Changes the size of the array of strings
*/

char	**add_elem_to_arr(char **arr, char *str, int free_str)
{
	char	**new;
	int		i;
	int		size;

	i = 0;
	size = ft_strarraylen(arr);
	new = malloc(sizeof(char *) * (size + 2));
	while (i < size)
	{
		new[i] = ft_strdup(arr[i]);
		free(arr[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	if (free_str)
		free(str);
	// str = NULL;
	i++;
	new[i] = NULL;
	free(arr);
	return (new);
}

void	exit_shell(char *message)
{
	if (message)
		ft_printf("minishell: %s", message);
	if (g_sh.input)
		free(g_sh.input);
	if (g_sh.input_tab)
		ft_strarr_free(g_sh.input_tab);
	if (g_sh.pwd)
		free(g_sh.pwd);
	if (g_sh.redirect)
		free(g_sh.redirect);
	if (g_sh.error)
		free(g_sh.error);
	ft_strarr_free(g_sh.env);
	exit(0);
}
