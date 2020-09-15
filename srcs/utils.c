/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:29:13 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/14 16:30:20 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_scr(void)
{
	ft_printf("\e[1;1H\e[2J");
}

void	init_shell(t_shell *sh)
{
	g_pwd = NULL;
	sh->lines = NULL;
	sh->input = NULL;
	sh->single_qt = 0;
	sh->double_qt = 0;
	sh->exit = 0;
	sh->comm = 0;
	sh->n = 0;
	sh->arg_1 = 0;
}

void	clear_shell(t_shell *sh)
{
	sh->lines = NULL;
	sh->single_qt = 0;
	sh->double_qt = 0;
	sh->exit = 0;
	sh->comm = 0;
	sh->n = 0;
	sh->arg_1 = 0;
}

void update_pwd()
{

	if (g_pwd)
		free(g_pwd);
	g_pwd = getcwd(NULL, 0);
}

void prompt_msg()
{
	update_pwd();
	ft_printf("%s: ", g_pwd);
}