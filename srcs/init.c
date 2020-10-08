/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 22:14:58 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/07 22:48:27 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Copies the environment variable of the parent shell to the g_sh
*/

void	init_env(char **env)
{
	int i;

	i = 0;
	g_sh.env = ft_memalloc(sizeof(char *) * (ft_arraylen((void **)env) + 1));
	while (env[i])
	{
		if (!(g_sh.env[i] = ft_strdup(env[i])))
			exit_shell(errno);
		i++;
	}
}

/*
** Saves stdin and stdout file descriptors.
*/

void 	init_fd(void)
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

/*
** Initializes shell at start start.
*/

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
