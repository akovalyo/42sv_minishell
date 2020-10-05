/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:08:33 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/05 16:13:04 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_redir(t_list *lst)
{
	g_sh.fd[2] = open(lst->content, O_RDONLY);
	if (g_sh.fd[2] < 0)
	{
		print_error(strerror(errno), errno);
		return ;
	}
	if((dup2(g_sh.fd[2], 0)) < 0)
	{
		print_error(strerror(errno), errno);
		return ;
	}
}

void	output_redir(t_list *lst)
{
	if (lst->ctg == GR_SIGN)
		g_sh.fd[3] = open(lst->content, (O_CREAT | O_WRONLY | O_TRUNC), 0666);
	else if (lst->ctg == DB_GR_SIGN)
		g_sh.fd[3] = open(lst->content, (O_CREAT | O_WRONLY | O_APPEND), 0666);
	if (g_sh.fd[3] < 0)
	{
		print_error(strerror(errno), errno);
		return ;
	}
	if((dup2(g_sh.fd[3], 1)) < 0)
	{
		print_error(strerror(errno), errno);
		return ;
	}
}

void	restore_fd(void)
{
	if (g_sh.map_len > 1)
	{
		if (g_sh.fd[2])
		{
			close(g_sh.fd[2]);
			g_sh.fd[2] = 0;
			close(0);
		}
		if (g_sh.fd[3])
		{
			close(g_sh.fd[3]);
			g_sh.fd[3] = 0;
			close(0);
		}
		if ((dup2(g_sh.fdio[1], 1)) < 0)
		{
			print_error(strerror(errno), errno);
			return ;
		}
		if ((dup2(g_sh.fdio[0], 0)) < 0)
		{
			print_error(strerror(errno), errno);
			return ;
		}
	}	
}

void pipe_connect(t_list *curr)
{
	int pipefd[2];
	
	if (curr)
	{
		pipe(pipefd);
		g_sh.fd[0] = pipefd[1];
		g_sh.fd[1] = pipefd[0];
		dup2(g_sh.fd[0], 1);
		close(g_sh.fd[0]);
		g_sh.fd[0] = 0;
	}
	else
	{
		dup2(g_sh.fd[1], 0);
		close(g_sh.fd[1]);
		g_sh.fd[1] = 0;
	}
}

void 	set_fd(void)
{
	t_list *lst;

	lst = NULL;
	if (g_sh.map[g_sh.map_i]->ctg == PIPE)
		pipe_connect(lst);
	else if (g_sh.map_i + 1 < g_sh.map_len)
	{
		lst = g_sh.map[g_sh.map_i + 1];
		if (lst->ctg == GR_SIGN || lst->ctg == DB_GR_SIGN)
			output_redir(lst);
		else if (lst->ctg == LESS_SIGN && (g_sh.map[g_sh.map_i]->comm != VOID && (g_sh.map[g_sh.map_i]->comm != NOCOMM)))
			input_redir(lst);
		else if (lst->ctg == PIPE)
			pipe_connect(lst);
	}
}