/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:22:19 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/07 22:30:48 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Called function if Ctrl+C interrupt the parent process.
*/

void	signal_in_parent(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		ft_printf("%s: ", get_pwd());
	}
}

/*
** Called function if Ctrl+C interrupt the child process.
*/

void	signal_in_child(int sig)
{
	ft_printf("\n");
	(void)sig;
}

/*
** Handles signals in the shell
*/

void	signal_parent(void)
{
	if (signal(SIGINT, signal_in_parent) == SIG_ERR)
	{
		print_error(strerror(errno), errno);
		return ;
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		print_error(strerror(errno), errno);
		return ;
	}
}

/*
**	Handles signals in the child process
*/

void	signal_child(void)
{
	if (signal(SIGINT, signal_in_child) == SIG_ERR)
	{
		print_error(strerror(errno), errno);
		return ;
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		print_error(strerror(errno), errno);
		return ;
	}
}
