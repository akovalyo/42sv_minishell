/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:29:13 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/05 16:39:45 by akovalyo         ###   ########.fr       */
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
	g_sh.fd[0] = 0;
	g_sh.fd[1] = 0;
	g_sh.fd[2] = 0;
	g_sh.fd[3] = 0;
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
	g_sh.rewrite = 0;
	g_sh.red_count = 0;
	g_sh.map = NULL;
	g_sh.map_i = 0;
	g_sh.map_len = 0;
	g_sh.map_next = 0;
	g_sh.pipe = 0;
	g_sh.status[0] = 0;
	g_sh.status[1] = 0;
}

void	clear_shell(void)
{
	clear_tokens();
	ft_strarr_free(g_sh.input_tab);
	g_sh.input_tab = NULL;
	g_sh.sn_qt = 0;
	g_sh.db_qt = 0;
	g_sh.exit = 0;
	g_sh.n_comm = 0;
	g_sh.flag = 1;
	g_sh.fl_ignore = 0;
	g_sh.rewrite = 0;
	g_sh.error = 0;
	g_sh.status[1] = g_sh.status[0];
	g_sh.status[0] = 0;
}

char	*get_pwd(void)
{
	char *pwd;

	pwd = get_env("PWD");
	if (pwd)
		return (pwd);
	else
	{
		print_error("failed to load env variable", 1);
		return (NULL);
	}

}