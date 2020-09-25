/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:11:13 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/25 16:39:04 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Changes the size of the array of strings
*/

char	**arr_realloc(char **arr, int size)
{
	char	**new;
	int		i;

	i = 0;
	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		new[i] = ft_strdup(arr[i]);
		free(arr[i]);
		i++;
	}
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
	ft_strarr_free(g_sh.env);
	exit(0);
}
