/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:11:13 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/24 22:36:24 by akovalyo         ###   ########.fr       */
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

// void	free_pars(void)
// {
// 	t_list	*tmp;

// 	while (g_sh.pars)
// 	{
// 		tmp = g_sh.pars->next;
// 		if (g_sh.pars->content)
// 			free(g_sh.pars->content);
// 		free(g_sh.pars);
// 		g_sh.pars = tmp;
// 	}
// }