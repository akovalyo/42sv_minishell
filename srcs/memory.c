/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:11:13 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/30 15:05:58 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Changes the size of the array of strings
*/

char	**add_elem_to_arr(char **arr, char *str, void (*del)(void *))
{
	char	**new;
	int		i;
	int		size;

	i = 0;
	size = ft_arraylen((void **)arr);
	new = malloc(sizeof(char *) * (size + 2));
	while (i < size)
	{
		new[i] = ft_strdup(arr[i]);
		free(arr[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	if (del)
		del(str);
	i++;
	new[i] = NULL;
	free(arr);
	return (new);
}

void	print_error(char *err)
{
	ft_printf("minishell: %s\n", err);
}

void	exit_shell(int err)
{
	if (err)
		print_error(strerror(err));
	free(g_sh.input);
	ft_strarr_free(g_sh.input_tab);
	free(g_sh.pwd);
	free(g_sh.redirect);
	free(g_sh.map);
	ft_strarr_free(g_sh.env);
	exit(0);
}
