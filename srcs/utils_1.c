/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:29:13 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/29 17:31:15 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_scr(void)
{
	ft_printf("\e[1;1H\e[2J");
}

void	init_shell(void)
{
	clear_scr();
	g_sh.pwd = NULL;
	g_sh.input_tab = NULL;
	g_sh.error = NULL;
	g_sh.sn_qt = 0;
	g_sh.db_qt = 0;
	g_sh.exit = 0;
	g_sh.comm = VOID;
	g_sh.n_comm = 0;
	g_sh.tokens = NULL;
	g_sh.flag = 1;
	g_sh.fl_ignore = 0;
	g_sh.redirect = NULL;
	g_sh.rewrite = 0;
	g_sh.red_count = 0;
	g_sh.map = NULL;
	g_sh.map_i = 0;
}

void	clear_shell(void)
{
	ft_strarr_free(g_sh.input_tab);
	g_sh.input_tab = NULL;
	g_sh.sn_qt = 0;
	g_sh.db_qt = 0;
	g_sh.exit = 0;
	g_sh.comm = VOID;
	g_sh.n_comm = 0;
	g_sh.flag = 1;
	g_sh.fl_ignore = 0;
	g_sh.rewrite = 0;
	g_sh.red_count = 0;
	free(g_sh.redirect);
	g_sh.redirect = NULL;
	free(g_sh.error);
	g_sh.error = NULL;
	free(g_sh.map);
	g_sh.map = NULL;
	g_sh.map_i = 0;	
}

void update_pwd(void)
{

	if (g_sh.pwd)
		free(g_sh.pwd);
	g_sh.pwd = getcwd(NULL, 0);
}

void prompt_msg(void)
{
	update_pwd();
	ft_printf("%s: ", g_sh.pwd);
}