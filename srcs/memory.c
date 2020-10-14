/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:11:13 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/13 18:22:07 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_next_redir(int i)
{
	if ((g_sh.map[i]->ctg == GR_SIGN || g_sh.map[i]->ctg == DB_GR_SIGN) &&
	(g_sh.map[i + 1]->ctg == GR_SIGN || g_sh.map[i + 1]->ctg == DB_GR_SIGN))
		return (1);
	return (0);
}

void 	delete_map_pos(int i)
{
	while (i + 1 < g_sh.map_len)
	{
		g_sh.map[i] = g_sh.map[i + 1];
		i++;
	}
	g_sh.map[i] = NULL;

}

void	update_map(void)
{
	int i;
	int fd;

	i = 0;
	while (i < g_sh.map_len)
	{
		if (i + 1 < g_sh.map_len && check_next_redir(i))
		{
			fd = open(g_sh.map[i]->content, (O_CREAT | O_WRONLY | O_TRUNC), 0666);
			close(fd);
			delete_map_pos(i);
			g_sh.map_len--;
			i--;
		}
		i++;
	}
}

/*
** Allocates memory for file descriptor's queue of conected processes.
*/

void	allocate_fd(void)
{
	int i;

	i = -1;
	update_map();
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
** Frees memory of the fd array.
*/

void	fd_free(void)
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
** Reinitializes g_sh struct between 2 command lines.
*/

void	clear_inner(void)
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
** Frees memory before exit and exits sheel.
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
