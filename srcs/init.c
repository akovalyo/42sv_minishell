/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 22:14:58 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/16 15:59:07 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Creates connections between processes, for redirections open file and
** saves file descriptors in fd array.
*/

void	set_fd_global(void)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (g_sh.map_len <= 1)
		return ;
	allocate_fd();
	while (++i < g_sh.map_len)
	{
		if (g_sh.map[i]->ctg == PIPE)
			j = pipe_connect(j);
		if (g_sh.map[i]->ctg == GR_SIGN || g_sh.map[i]->ctg == DB_GR_SIGN)
			j = output_redir(i, j);
		if (g_sh.map[i]->ctg == LESS_SIGN)
			j = input_redir(i, j);
	}
}

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
	change_envv("OLDPWD", get_envv("PWD"), NULL);
}

/*
** Saves stdin and stdout file descriptors.
*/

void	init_fd(void)
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
	g_sh.map = NULL;
	g_sh.map_i = 0;
	g_sh.map_len = 0;
	change_envv("STATUS", "0", NULL);
}
