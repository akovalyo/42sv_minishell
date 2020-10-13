/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:55:46 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/13 12:44:53 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Action if no bin or builtin has been found
*/

void	comm_void(char **arg)
{
	(void)arg;
	if (g_sh.map[g_sh.map_i]->comm == VOID)
		ft_printf("");
	else if (g_sh.map[g_sh.map_i]->comm == NOCOMM)
	{
		if (ft_strncmp(g_sh.tokens->content, "clear", 6) == 0)
			clear_scr();
		else
		{
			g_sh.error++;
			g_sh.status[0] = 1;
			ft_printf("minishell: command not found: %s\n",
									g_sh.tokens->content);
		}
	}
}

/*
** Executes the binary file
*/

void	comm_sh(char **arg)
{
	pid_t	pid;
	int		status;

	(void)arg;
	pid = fork();
	if (pid < 0)
		return (print_error("failed to create a new process", 1));
	else if (pid == 0)
	{
		execve(arg[0], arg, g_sh.env);
	}
	else
	{
		signal_child();
		waitpid(pid, &status, 0);
		g_sh.status[0] = WEXITSTATUS(status);
	}
}

/*
** Executes builtins or binary file
*/

void	exec_comm(void)
{
	static void	(*exec_comm[])(char **arg) = {comm_void, comm_echo,
				comm_pwd, comm_cd, comm_export, comm_unset, comm_env,
				comm_void};
	char		**arg;
	t_list		*lstptr;

	lstptr = g_sh.map[g_sh.map_i];
	if (is_redirect_ctg(lstptr))
		return ;
	arg = create_argv(g_sh.map[g_sh.map_i]);
	if (g_sh.map[g_sh.map_i]->comm == SH)
		comm_sh(arg);
	else
		exec_comm[g_sh.map[g_sh.map_i]->comm](arg);
	ft_strarr_free(arg);
}

/*
** Process every command in the command's queue.
*/

void	handle_input(void)
{
	int		i;

	i = 0;
	while (g_sh.input_tab[i])
	{
		parser(g_sh.input_tab[i]);
		g_sh.map_len = ft_arraylen((void **)g_sh.map);
		set_fd_global();
		if (g_sh.error)
			return ;
		while (g_sh.map_i < g_sh.map_len)
		{
			set_fd(g_sh.map_i);
			if (g_sh.exit)
				exit_shell(errno);
			exec_comm();
			restore_fd(g_sh.map_i);
			g_sh.map_i++;
		}
		clear_inner();
		i++;
	}
}

/*
** Starts, initializes minishell. Gets input from user and
** splits if needed into multiple commands.
*/

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	init_shell();
	init_env(env);
	while (1)
	{
		ft_printf("\033[1;35m%s: \033[0m", get_pwd());
		signal_parent();
		g_sh.input_tab = read_input();
		handle_input();
		clear_shell();
	}
	ft_strarr_free(g_sh.env);
	return (0);
}
