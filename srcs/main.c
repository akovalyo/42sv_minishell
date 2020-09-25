/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:55:46 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/25 16:58:26 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**read_input()
{
	char	**tab_input;
	int		tab_len;
	int		i;
	int		ret;

	i = 0;
	if ((ret = get_next_line(0, &(g_sh.input))) < 0)
		exit_shell("read error");
	else if (ret == 0)
		exit_shell(NULL);
	tab_input = ft_strsplit(g_sh.input, ';');
	free(g_sh.input);
	g_sh.input = NULL;
	return (tab_input);
}

void	comm_void(char **tab_comm)
{
	ft_printf("minishell: command not found: %s\n", tab_comm[0]);
}

void		comm_echo(char **tab_comm)
{
	int i;
	int len;

	i = 0;
	if (ft_strarraylen(tab_comm) == 1)
		ft_printf("\n");
	else
	{
		len = ft_strlen(tab_comm[1]);
		if (ft_strncmp(tab_comm[1], "-n ", 3) == 0)
		{
			g_sh.n = 1;
			i = 3;
		}
		while (i < len)
		{

		}
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

void		comm_cd(char **tab_comm)
{
	return ;
}

void		comm_export(char **tab_comm)
{
	return ;
}

void		comm_unset(char **tab_comm)
{
	return ; 
}

void		comm_env(char **tab_comm)
{
	return ;
}

void		comm_sh(char **tab_comm)
{	
	char	**argv;
	pid_t	pid;
	
	argv = create_argv(tab_comm);
	pid = fork();
	if (pid == 0)
		execve(argv[0], argv, g_sh.env);
	else if (pid < 0)
		ft_printf("minishell: failed to create a new process\n");
	wait(&pid);
	ft_strarr_free(argv);
}

void 	add_to_argv_rest(char **new, t_list *lstptr, int i)
{
	char *tmp;
	char *rest;
	
	rest = NULL;
	if (lstptr && lstptr->ctg == SP)
		lstptr = lstptr->next;
	while (lstptr)
	{
		tmp = rest;
		rest = ft_strjoin(rest, lstptr->content);
		if (tmp)
			free(tmp);
		lstptr = lstptr->next;
	}
	if (rest)
	{
		new[i] = ft_strdup(rest);
		free(rest);
	}
	else
		new[i] = NULL;
}

char **create_argv(char **tab_comm)
{
	char	**new;
	int		size;
	int		i;
	t_list 	*lstptr;

	size = ft_strarraylen(tab_comm) > 1 == 1 ? 1 : 0;
	size = size + g_sh.flags + 2;
	new = malloc(sizeof(char *) * size);
	new[0] = ft_strdup(tab_comm[0]);	
	new[size - 1] = NULL;
	lstptr = g_sh.pars;
	i = 1;
	while (i < (size - 1) && g_sh.flags > 0)
	{
		if (lstptr->ctg == FLAG)
		{
			new[i] = ft_strdup(lstptr->content);
			g_sh.flags--;
			i++;
		}
		lstptr = lstptr->next;
	}
	if (i < (size - 1))
		add_to_argv_rest(new, lstptr, i);
	return (new);
}

/*
** Checks existing system executable for the first argument in the input
*/

int 		check_bin(char *comm)
{
	char			**paths;
	int				i;
	struct stat		buf;

	i = 0;
	if(!(paths = ft_strsplit(get_env("PATH="), ':')))
		return (0);
	while (paths[i])
	{
		if (ft_strncmp(paths[i], comm, ft_strlen(paths[i])) == 0) 
		{
			if (lstat(comm, &buf) == 0)
			{
				ft_strarr_free(paths);
				return (1);
			}
		}	
		i++;
	}
	ft_strarr_free(paths);
	return (0);
}

void		check_builtins_and_bin(char **tab_comm)
{
	if (ft_strnequ_alpha(tab_comm[0], "exit", 5) == 0)
		g_sh.exit = 1;
	else if (ft_strnequ_alpha(tab_comm[0], "echo", 5) == 0)
		g_sh.comm = ECHO;
	else if (ft_strnequ_alpha(tab_comm[0], "pwd", 4) == 0)
		g_sh.comm = PWD;
	else if (ft_strnequ_alpha(tab_comm[0], "cd", 3) == 0)
		g_sh.comm = CD;
	else if (ft_strnequ_alpha(tab_comm[0], "export", 7) == 0)
		g_sh.comm = EXPORT;
	else if (ft_strnequ_alpha(tab_comm[0], "unset", 6) == 0)
		g_sh.comm = UNSET;
	else if (ft_strnequ_alpha(tab_comm[0], "env", 4) == 0)
		g_sh.comm = ENV;
	else if (check_bin(tab_comm[0]))
		g_sh.comm = SH;

	
}

char	**parse_cmd(char *comm)
{
	int		start;
	int		end;
	int		len;
	char	*cmd;
	char	**tab_comm;

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
	tab_comm[0] = ft_strdup(cmd);
	free(cmd);
	tab_comm[start] = NULL;
	if (start > 1)
		tab_comm[1] = ft_strtrim(&comm[end]);
	return (tab_comm);
}

/*
** 
*/

void	exec_input()
{
	int				i;
	char			**tab_comm;
	char			**tmp;
	int				ret;
	static void		(*exec_comm[])(char**) = {comm_void, comm_echo, comm_pwd,
					comm_cd, comm_export, comm_unset, comm_env, comm_sh};
	
	i = 0;
	while (g_sh.input_tab[i])
	{
		tab_comm = parse_cmd(g_sh.input_tab[i]);
		check_builtins_and_bin(tab_comm);
		if (ft_strarraylen(tab_comm) > 1)
		{
			parser(tab_comm[1]);
		}
		if (g_sh.exit)
		{
			ft_strarr_free(tab_comm);
			exit_shell(NULL);
		}
		exec_comm[g_sh.comm](tab_comm);
		ft_lstclear(&(g_sh.pars), free);
		ft_strarr_free(tab_comm);
		i++;
	}
}

int		main(int argc, char **argv, char **env)
{
	init_shell();
	init_env(env);
	while (1)
	{
		prompt_msg();
		signal(SIGINT, sig_func);
		signal(SIGQUIT, sig_sl);
		g_sh.input_tab = read_input();
		
		exec_input();
		
		if (g_sh.input_tab)
			ft_strarr_free(g_sh.input_tab);
		clear_shell();
	}
	ft_strarr_free(g_sh.env);
	return (0);
}
