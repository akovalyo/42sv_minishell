/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:08:33 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/14 18:16:48 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Open file used in stdin redirection.
*/

int		input_redir(int i, int j)
{
	int fd;

	if (g_sh.gfd[j][2])
		close(g_sh.gfd[j][3]);
	fd = open(g_sh.map[i]->content, O_RDONLY);
	if (fd < 0)
	{
		print_error(strerror(errno), errno);
		return (j);
	}
	g_sh.gfd[j][2] = 1;
	g_sh.gfd[j][3] = fd;
	return (j);
}

/*
** Open files used in stdout redirection.
*/

int		output_redir(int i, int j)
{
	int fd;

	if (g_sh.gfd[j][0])
		close(g_sh.gfd[j][1]);
	if (g_sh.map[i]->ctg == GR_SIGN)
		fd = open(g_sh.map[i]->content, (O_CREAT | O_WRONLY | O_TRUNC), 0666);
	else if (g_sh.map[i]->ctg == DB_GR_SIGN)
		fd = open(g_sh.map[i]->content, (O_CREAT | O_WRONLY | O_APPEND), 0666);
	if (fd < 0)
	{
		print_error(strerror(errno), errno);
		return (j);
	}
	g_sh.gfd[j][0] = 1;
	g_sh.gfd[j][1] = fd;
	return (j);
}

/*
** Restores file descriptors before the next command.
*/

void	restore_fd(int i)
{
	if (!g_sh.gfd)
		return ;
	if (g_sh.gfd[i][0])
	{
		if ((dup2(g_sh.fdio[1], 1)) < 0)
			print_error(strerror(errno), errno);
	}
	if (g_sh.gfd[i][2])
	{
		if ((dup2(g_sh.fdio[0], 0)) < 0)
			print_error(strerror(errno), errno);
	}
}

/*
** Creates connection between two processes.
*/

int		pipe_connect(int j)
{
	int pipefd[2];

	pipe(pipefd);
	g_sh.gfd[j][0] = 1;
	g_sh.gfd[j][1] = pipefd[1];
	g_sh.gfd[j + 1][2] = 1;
	g_sh.gfd[j + 1][3] = pipefd[0];
	return (j + 1);
}

/*
** Sets file descriptors for current process.
*/

void	set_fd(int j)
{
	if (!g_sh.gfd)
		return ;
	if (g_sh.gfd[j][0])
	{
		if ((dup2(g_sh.gfd[j][1], 1)) < 0)
		{
			print_error(strerror(errno), errno);
			return ;
		}
		close(g_sh.gfd[j][1]);
	}
	if (g_sh.gfd[j][2])
	{
		if ((dup2(g_sh.gfd[j][3], 0)) < 0)
		{
			print_error(strerror(errno), errno);
			return ;
		}
		close(g_sh.gfd[j][3]);
	}
}
