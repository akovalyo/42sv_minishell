/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:55:46 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/18 12:56:02 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(char *message)
{
	if (message)
		ft_printf("minishell: %s", message);
	if (g_sh.input)
		free(g_sh.input);
	if (g_sh.input_tab)
		ft_strtab_free(g_sh.input_tab);
	if (g_sh.pwd)
		free(g_sh.pwd);
	ft_strtab_free(g_sh.env);
	exit(0);
}

char	**read_input()
{
	char	**tab_input_tab;
	int		tab_len;
	int		i;
	int		ret;

	i = 0;
	if ((ret = get_next_line(0, &(g_sh.input))) < 0)
		exit_shell("read error");
	else if (ret == 0)
		exit_shell(NULL);
	tab_input_tab = ft_strsplit(g_sh.input, ';');
	free(g_sh.input);
	g_sh.input = NULL;
	return (tab_input_tab);
}

void	comm_void(char **tab_comm)
{
	//execve("/bin/pwd", tab_comm + 1, g_sh.env);
	ft_printf("minishell: command not found: %s\n", tab_comm[0]);
}

int 		isquote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

void		comm_echo(char **tab_comm)
{
	if (ft_strarraylen(tab_comm) == 1)
		ft_printf("\n");
	if (ft_strarraylen(tab_comm) > 1)
	{
		if (ft_strncmp(tab_comm[1], "-n", 3) == 0)
			g_sh.n = 1;
		ft_printf("%s\n", tab_comm[1]);
	}
}

void		comm_pwd(char **tab_comm)
{
	if (ft_strarraylen(tab_comm) > 1)
		ft_printf("minishell: too many arguments\n");
	else
	{
		update_pwd();
		ft_printf("%s\n", g_sh.pwd);
	}
}

void		check_builtins(char **tab_comm)
{
	//ft_printf("%s\n", tab_comm[1]);
	if (ft_strncmp(tab_comm[0], "exit", 5) == 0)
		g_sh.exit = 1;
	else if (ft_strncmp(tab_comm[0], "echo", 5) == 0)
		g_sh.comm = ECHO;
	else if (ft_strncmp(tab_comm[0], "pwd", 4) == 0)
		g_sh.comm = PWD;

}

char			**parse_cmd(char *comm)
{
	int start;
	int end;
	int len;
	char *cmd;
	char **tab_comm;

	len = ft_strlen(comm);
	start = 0;
	while (ft_isspace(comm[start]))
		start++;
	end = start;
	while (comm[end] && ft_isspace(comm[end]) == 0)
		end++;
	cmd = ft_strsub(comm, start, end - start);
	start = (len - end > 0) ? 2 : 1;
	tab_comm = malloc(sizeof(char *) * (start + 1));
	tab_comm[0] = cmd;
	tab_comm[start] = NULL;
	if (start > 1)
		tab_comm[1] = ft_strtrim(&comm[end]);
		//tab_comm[1] = ft_strsub(comm, end, len - end);
	return (tab_comm);
}

// void		parse_comm_line(char *comm)
// {
// 	parse_cmd(comm);
// }

void		check_comm_line(char **comm)
{
	
	//parse_comm_line(comm);
	check_builtins(comm);
	
}

void	exec_input()
{
	int		i;
	char	**tab_comm;
	int				ret;
	static void		(*exec_comm[])(char**) = {comm_void, comm_echo, comm_pwd};
	
	i = 0;
	while (g_sh.input_tab[i])
	{
		//tab_comm = ft_strsplit_space(g_sh.input_tab[i]);
		tab_comm = parse_cmd(g_sh.input_tab[i]);
		check_comm_line(tab_comm);
		if (g_sh.exit)
			exit_shell(NULL);
		// else if (!sh->comm)
		// 	ft_printf("minishell: command not found: %s\n", tab_comm[0]);
		exec_comm[g_sh.comm](tab_comm);
		ft_strtab_free(tab_comm);
		i++;
	}
}

void	init_env(char **env)
{
	int i;

	i = 0;
	g_sh.env = ft_memalloc(sizeof(char *) * (ft_strarraylen(env) + 1));
	while (env[i])
	{
		
		if (!(g_sh.env[i] = ft_strdup(env[i])))
			exit_shell(NULL);
		
		// ft_printf("%s\n", g_sh.env[i]);
		i++;
	}
}

int		main(int argc, char **argv, char **env)
{
	init_shell();
	init_env(env);
	
	// int i = 1;
	// while (env[i])
	// {
	// 	ft_printf("%s\n", env[i]);
	// 	i++;
	// }
	while (1)
	{
		prompt_msg();
		signal(SIGINT, sig_func);
		signal(SIGQUIT, sig_sl);
		g_sh.input_tab = read_input();
		exec_input();
		if (g_sh.input_tab)
			ft_strtab_free(g_sh.input_tab);
		clear_shell();
	}
	ft_strtab_free(g_sh.env);
	return (0);
}
