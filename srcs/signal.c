/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:22:19 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/12 17:36:03 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Processes Ctrl+C interrupt in the parent process.
*/

void	signal_in_parent(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\b\b  \n");
		ft_printf("\033[1;35m%s: \033[0m", get_pwd());
	}
}

/*
** Processes Ctrl+C interruption in the child process.
*/

void	signal_in_child(int sig)
{
	ft_printf("\n");
	(void)sig;
}

/*
** Processes Ctrl+\ interruption.
*/

void	signal_sl(int sig)
{
	ft_printf("\b\b  \b\b");
	(void)sig;
}

/*
** Handles signals in the shell.
*/

void	signal_parent(void)
{
	if (signal(SIGINT, signal_in_parent) == SIG_ERR)
	{
		print_error(strerror(errno), errno);
		return ;
	}
	if (signal(SIGQUIT, signal_sl) == SIG_ERR)
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
	if (signal(SIGQUIT, signal_sl) == SIG_ERR)
	{
		print_error(strerror(errno), errno);
		return ;
	}
}
