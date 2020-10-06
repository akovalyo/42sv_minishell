/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:08:33 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/06 11:31:08 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_redir(t_list *lst, int i)
{
	int fd;

	g_sh.gfd[i][2] = 1;
	g_sh.gfd[i][3] = open(lst->content, O_RDONLY);
	
	if (g_sh.gfd[i][3] < 0)
		print_error(strerror(errno), errno);
}

void	output_redir(t_list *lst, int i)
{
	if (lst->ctg == GR_SIGN)
	{
		g_sh.gfd[i][0] = 1;
		g_sh.gfd[i][1] = open(lst->content, (O_CREAT | O_WRONLY | O_TRUNC), 0666);
	}
	else if (lst->ctg == DB_GR_SIGN)
	{
		g_sh.gfd[i][0] = 1;
		g_sh.gfd[i][1] = open(lst->content, (O_CREAT | O_WRONLY | O_APPEND), 0666);
	}
	if (g_sh.gfd[i][1] < 0)
		print_error(strerror(errno), errno);
}

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

void pipe_connect(int i)
{
	int pipefd[2];

	pipe(pipefd);
	g_sh.gfd[i - 1][0] = 1;
	g_sh.gfd[i - 1][1] = pipefd[1];
	g_sh.gfd[i][2] = 1;
	g_sh.gfd[i][3] = pipefd[0];	
}

void 	set_fd(int i)
{
	if (!g_sh.gfd)
		return ;
	if (g_sh.gfd[i][0])
	{
		if((dup2(g_sh.gfd[i][1], 1)) < 0)
		{
			print_error(strerror(errno), errno);
			return ;
		}
		close(g_sh.gfd[i][1]);
	}
	if (g_sh.gfd[i][2])
	{
		if((dup2(g_sh.gfd[i][3], 0)) < 0)
		{
			print_error(strerror(errno), errno);
			return ;
		}
		close(g_sh.gfd[i][3]);
	}
}