/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:11:13 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/06 20:40:45 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Adds str to the array of strings
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

void	print_error(char *err, int err_n)
{
	g_sh.error = 1;
	g_sh.status[0] = err_n;
	ft_printf("minishell: %s\n", err);
}

void	fd_free()
{
	int i;

	if (!g_sh.gfd)
		return ;
	i = -1;
	while (++i < g_sh.map_len)
		free(g_sh.gfd[i]);
	free(g_sh.gfd);
	g_sh.gfd = 0;
}


void 	clear_inner(void)
{
	fd_free();
	ft_lstclear(&(g_sh.tokens), free);
	g_sh.tokens = NULL;
	free(g_sh.map);
	g_sh.map = NULL;
	g_sh.map_i = 0;
	g_sh.map_len = 0;	
}

void	exit_shell(int err)
{
	if (err)
		print_error(strerror(err), err);

	clear_inner();
	free(g_sh.input);
	ft_strarr_free(g_sh.input_tab);
	ft_strarr_free(g_sh.env);
	exit(0);
}
