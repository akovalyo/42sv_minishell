/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:55:46 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/22 09:29:44 by alex             ###   ########.fr       */
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

void convert_arguments(char **tab_comm)
{
	int i;

	
}

void		comm_sh(char **tab_comm)
{	
	pid_t pid;
	
	if (ft_strarraylen(tab_comm) > 1 &&	strlen(tab_comm[1]) == 0)
	{
		free(tab_comm[1]);
		tab_comm[1] = NULL;
	}
	//ft_printf("%d\n", ft_strarraylen(tab_comm));
	pid = fork();
	if (pid == 0)
		execve(tab_comm[0], tab_comm, g_sh.env);
	else if (pid < 0)
		ft_printf("minishell: failed to create a new process\n");
	wait(&pid);
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
				return (1);
		}	
		i++;
	}
	return (0);
}

/*
** Returns pointer to the value of the environment variable 'var' if found, else NULL
*/

char		*get_env(char *var)
{
	int i;

	i = 0;
	while (g_sh.env[i])
	{
		if (ft_strncmp(g_sh.env[i], var, ft_strlen(var)) == 0)
			return (ft_strchr(g_sh.env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

void		check_builtins_and_bin(char **tab_comm)
{
	//ft_printf("%s\n", tab_comm[1]);
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
	
	return (tab_comm);
}

int		get_index_arg(char *comm)
{
	// char *arg;
	// char *tmp;
	int len;
	int i;
	// int start;

	
	i = 0;
	// start  = 0;
	
	
	// while (comm[i] && ft_isspace(comm[i]))
	// 	i++;
	// start = i;
	
	if (ft_strlen(comm) > 1 && comm[i++] == '-')
	{
		if (ft_isalpha(comm[i]))
		{
			
			while (comm[i] && ft_isalpha(comm[i]))
				i++;
			len = ft_strlen(comm) - i;
			if (len == 0)
				return (0);
			
			// arg = ft_strsub(*comm, start, i);
			// tmp = *comm;
			// *comm = ft_strsub(*comm, i, len);
			
			// free(tmp);

			return (i - 1);
		}
	}

	return (0);
}

char **tab_realloc(char **tab, int size)
{
	char **new;
	int i;

	i = 0;
	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		new[i] = tab[i];
		i++;
	}
	new[i] = NULL;
	free(tab);
	ft_printf("%d\n", ft_strarraylen(new));
	return (new);
}

void		parse_arg(char **tab_comm)
{
	int ind;
	char *tmp;
	int i;
	int j;

	i = 1;
	
	while ((ind = get_index_arg(tab_comm[i])) != 0)
	{	
		i++;
		tab_comm = tab_realloc(tab_comm, i + 1);

		// ft_printf("%d\n", ft_strarraylen(tab_comm));
		
		tab_comm[i] = ft_strsub(tab_comm[i - 1], ind + 1, ft_strlen(tab_comm[i - 1]) - ind);
		tmp = tab_comm[i - 1];
		tab_comm[i - 1] = ft_strsub(tab_comm[i - 1], 0, ind);
		free(tmp);

		j = -1;
		while (tab_comm[j++])
			ft_printf("%s\n", tab_comm[j]);
 
		//free(arg);
		//free(tmp);	
		
	}
}

// void		check_comm_line(char **comm)
// {
	
// 	//parse_comm_line(comm);
// 	check_builtins_and_bin(comm);
	
// }

void	exec_input()
{
	int				i;
	char			**tab_comm;
	//char			**tmp;
	int				ret;
	static void		(*exec_comm[])(char**) = {comm_void, comm_echo, comm_pwd,
					comm_cd, comm_export, comm_unset, comm_env, comm_sh};
	
	int j = -1;
	

	i = -1;
	while (g_sh.input_tab[i])
	{
		
		tab_comm = parse_cmd(g_sh.input_tab[i]);
		
		while (tab_comm[j++])
			ft_printf("%s\n", tab_comm[j]);


		check_builtins_and_bin(tab_comm);
		if (ft_strarraylen(tab_comm) > 1)
		{
			parse_arg(tab_comm);
		}

		// j = 0;
		while (tab_comm[j++])
			ft_printf("%s\n", tab_comm[j]);
		
		if (g_sh.exit)
			exit_shell(NULL);
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
			ft_strtab_free(g_sh.input_tab);
		clear_shell();
	}
	ft_strtab_free(g_sh.env);
	return (0);
}
