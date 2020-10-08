/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:11:13 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/07 22:44:20 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Allocates memory for file descriptor's queue of
** conected processes
*/

void 	allocate_fd(void)
{
	int i;

	i = -1;
	g_sh.gfd = malloc(sizeof(int *) * g_sh.map_len);
	while (++i < g_sh.map_len)
	{
		g_sh.gfd[i] = malloc(sizeof(int) * 4);
		g_sh.gfd[i][0] = 0;
		g_sh.gfd[i][1] = 0;
		g_sh.gfd[i][2] = 0;
		g_sh.gfd[i][3] = 0;
	}
}

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

/*
** Prints error and saves the error number to the 'g_sh' 
*/

void	print_error(char *err, int err_n)
{
	g_sh.error++;
	g_sh.status[0] = err_n;
	ft_printf("minishell: %s\n", err);
}

/*
** Frees memory of the fd array
*/

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

/*
**
*/

void 	clear_inner(void)
{
	fd_free();
	ft_lstclear(&(g_sh.tokens), free);
	g_sh.tokens = NULL;
	free(g_sh.map);
	g_sh.map = NULL;
	g_sh.map_i = 0;
	g_sh.map_len = 0;
	g_sh.error = 0;
}

/*
**
*/

void	exit_shell(int err)
{
	if (err == 1)
		print_error(strerror(err), err);
	clear_inner();
	free(g_sh.input);
	ft_strarr_free(g_sh.input_tab);
	ft_strarr_free(g_sh.env);
	exit(0);
}
