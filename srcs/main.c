/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:55:46 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/25 15:48:54 by akovalyo         ###   ########.fr       */
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
		ft_strarr_free(g_sh.input_tab);
	if (g_sh.pwd)
		free(g_sh.pwd);
	ft_strarr_free(g_sh.env);
	exit(0);
}

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

void 	add_to_argv_rest(char **new, t_list *lstptr, int i)
{
	char *tmp;
	char *rest;
	
	//ft_lstprint_str(lstptr);
	rest = NULL;
	if (lstptr && lstptr->ctg == SP)
		lstptr = lstptr->next;
	while (lstptr)
	{
		tmp = rest;
		rest = ft_strjoin(rest,lstptr->content);
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

int		addnode_spaces(char *arg, int i)
{
	int		start;
	t_list	*new;

	start = i;
	new = malloc(sizeof(t_list));
	while (arg[i] && ft_isspace(arg[i]))
		i++;
	new->content = NULL;
	new->content_size = 0;
	new->ctg = SP;
	new->atr = i - start;
	new->next = NULL;
	ft_lstadd_back(&(g_sh.pars), new);
	return (i);
}

int		addnode_flags(char *arg, int i)
{
	int 	start;
	t_list	*new;
	
	start = i;
	if (ft_isalpha(arg[i + 1]))
	{
		i++;
		while (arg[i] && ft_isalpha(arg[i]))
			i++;
		new = malloc(sizeof(t_list));
		g_sh.flags++;
		new->content = ft_strsub(arg, start, i - start);
		new->content_size = i - start;
		new->ctg = FLAG;
		new->atr = 0;
		new->next = NULL;
		ft_lstadd_back(&(g_sh.pars), new);
		return (i);
	}
	g_sh.fl_ignore = 1;
	return (start);
}

/*
** 
*/

int		addnode_envv(char *arg, int i)
{
	int 	start;
	t_list	*new;
	char 	*tmp;
	char	*ptr_env;
	
	start = i;
	i++;
	while (arg[i] && ft_isalpha(arg[i]))
		i++;
	new = malloc(sizeof(t_list));
	tmp = ft_strsub(arg, start, i - start);
	new->atr = 0;
	new->next = NULL;
	if ((ptr_env = get_env(tmp + 1)))
		new->content = ft_strdup(ptr_env);
	else
		new->content = ft_strdup(tmp);
	new->content_size = ft_strlen(new->content);
	new->ctg = STR;
	ft_lstadd_back(&(g_sh.pars), new);
	free(tmp);
	return (i);
}

int		addnode_tilde(char *arg, int i)
{
	int 	start;
	t_list	*new;
	char	*rest;
	char	*ptr;

	
	start = i + 1;
	i++;
	while (arg[i] && !special_char(arg[i]) && !ft_isspace(arg[i]))
		i++;
	new = malloc(sizeof(t_list));
	ptr = get_env("HOME");
	new->content = ft_strdup(ptr);
	if (start != i)
	{
		rest = ft_strsub(arg, start, i - start);
		ptr = new->content;
		new->content = ft_strjoin(new->content, rest);
		free(ptr);
		free(rest);
	}
	new->content_size = ft_strlen(new->content);
	new->atr = 0;
	new->next = NULL;
	new->ctg = STR;
	ft_lstadd_back(&(g_sh.pars), new);
	return (i);
}



int special_char(char c)
{
	if (c == '\'' || c == '"' || c == '<' || c == '>' || c == '$')
		return (1);
	return (0);
}

int		addnode_str(char *arg, int i)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->content = NULL;
	while (arg[i] && !special_char(arg[i]) && arg[i] != '$' && !ft_isspace(arg[i]))
	{	
		if (arg[i] == '\\')
			i++;
		new->content = ft_straddchr_free(new->content, arg[i]);
		i++;
	}
	new->content_size = ft_strlen(new->content);
	new->atr = 0;
	new->next = NULL;
	new->ctg = STR;
	ft_lstadd_back(&(g_sh.pars), new);
	return (i);
}

t_list 	*specialch_create_node(char *arg, int i)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (arg[i] == '\'')
	{
		new->ctg = SN_QT;
		g_sh.sn_qt += 1;
	}
	else if (arg[i] == '"')
	{
		new->ctg = DB_QT;
		g_sh.db_qt += 1;
	}
	else if (arg[i] == '<')
		new->ctg = LESS_SIGN;
	else if (arg[i] == '>')
	{
		if (arg[i + 1] == '>')
			new->ctg = DB_GR_SIGN;
		else
			new->ctg = GR_SIGN;
	}
	return (new);
}

int		addnode_specialch(char *arg, int i)
{
	t_list	*new;
	
	new = specialch_create_node(arg, i);
	if (new->ctg == SN_QT)
		new->content = ft_strdup("'");
	else if (new->ctg == DB_QT)
		new->content = ft_strdup("\"");
	else if (new->ctg == LESS_SIGN)
		new->content = ft_strdup("<");
	else if (new->ctg == GR_SIGN)
		new->content = ft_strdup(">");
	else if (new->ctg == DB_GR_SIGN)
		new->content = ft_strdup(">>");	
	new->content_size = 0;
	new->next = NULL;
	new->atr = 0;
	ft_lstadd_back(&(g_sh.pars), new);
	return (new->ctg == 11 ? i + 2 : i + 1);
}


void		parser(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (ft_isspace(arg[i]))
			i = addnode_spaces(arg, i);
		else if (arg[i] == '-' && !g_sh.fl_ignore)
			i = addnode_flags(arg, i);
		else if (arg[i] == '$')
			i = addnode_envv(arg, i);
		else if (arg[i] == '~')
			i = addnode_tilde(arg, i);
		else if (special_char(arg[i]))
			i = addnode_specialch(arg, i);
		else
			i = addnode_str(arg, i);
	}

}

void	exec_input()
{
	int				i;
	char			**tab_comm;
	char			**tmp;
	int				ret;
	static void		(*exec_comm[])(char**) = {comm_void, comm_echo, comm_pwd,
					comm_cd, comm_export, comm_unset, comm_env, comm_sh};
	
	int j = -1;
	

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
		//free_pars();
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
