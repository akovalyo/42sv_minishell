/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:29:13 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/23 12:29:00 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_scr(void)
{
	ft_printf("\e[1;1H\e[2J");
}

void	init_shell()
{
	clear_scr();
	g_sh.pwd = NULL;
	g_sh.input_tab = NULL;
	g_sh.input = NULL;
	g_sh.single_qt = 0;
	g_sh.double_qt = 0;
	g_sh.exit = 0;
	g_sh.comm = 0;
	g_sh.n = 0;
	g_sh.pars = NULL;
	g_sh.flags = 0;
	g_sh.fl_ignore = 0; 
}

void	clear_shell()
{
	g_sh.input_tab = NULL;
	g_sh.single_qt = 0;
	g_sh.double_qt = 0;
	g_sh.exit = 0;
	g_sh.comm = 0;
	g_sh.n = 0;
	g_sh.flags = 0;
	g_sh.fl_ignore = 0; 
}

void update_pwd()
{

	if (g_sh.pwd)
		free(g_sh.pwd);
	g_sh.pwd = getcwd(NULL, 0);
}

void prompt_msg()
{
	update_pwd();
	ft_printf("%s: ", g_sh.pwd);
}