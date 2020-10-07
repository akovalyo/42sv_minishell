/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:29:13 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/07 11:05:48 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_scr(void)
{
	ft_printf("\e[1;1H\e[2J");
}

void 	init_fd()
{
	if ((g_sh.fdio[0] = dup(0)) < 0)
	{
		print_error(strerror(errno), errno);
		return ;
	}
	if ((g_sh.fdio[1] = dup(1)) < 0)
	{
		print_error(strerror(errno), errno);
		return ;
	}
	g_sh.gfd = 0;
}

void	init_shell(void)
{
	clear_scr();
	init_fd();
	g_sh.input_tab = NULL;
	g_sh.error = 0;
	g_sh.sn_qt = 0;
	g_sh.db_qt = 0;
	g_sh.exit = 0;
	g_sh.n_comm = 0;
	g_sh.tokens = NULL;
	g_sh.flag = 1;
	g_sh.fl_ignore = 0;
	g_sh.map = NULL;
	g_sh.map_i = 0;
	g_sh.map_len = 0;
	g_sh.status[0] = 0;
	g_sh.status[1] = 0;
}

void	clear_shell(void)
{
	clear_inner();
	ft_strarr_free(g_sh.input_tab);
	g_sh.input_tab = NULL;
	g_sh.sn_qt = 0;
	g_sh.db_qt = 0;
	g_sh.exit = 0;
	g_sh.n_comm = 0;
	g_sh.flag = 1;
	g_sh.fl_ignore = 0;

	g_sh.status[1] = g_sh.status[0];
	g_sh.status[0] = 0;
}

char	*get_pwd(void)
{
	char *pwd;

	if (!(pwd = get_envv("PWD")))
		return (NULL);
	return (pwd);
}