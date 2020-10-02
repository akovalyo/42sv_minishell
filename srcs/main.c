/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:55:46 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/02 12:41:01 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**read_input(void)
{
	char	**tab_input;
	int		tab_len;
	int		i;
	int		ret;

	i = 0;
	if ((ret = get_next_line(0, &(g_sh.input))) < 0)
		exit_shell(errno);
	else if (ret == 0)
		exit_shell(errno);
	tab_input = ft_strsplit(g_sh.input, ';');
	free(g_sh.input);
	g_sh.input = NULL;
	return (tab_input);
}

void	comm_void(char **arg, int map_i)
{
	if (g_sh.map[map_i]->comm == VOID)
		ft_printf("");
	else if (g_sh.map[map_i]->comm == NOCOMM)
		ft_printf("minishell: command not found: %s\n", g_sh.tokens->content);
}

void		comm_echo(char **arg, int map_i)
{
	int i;
	int len;

	i = 1;
	len = ft_arraylen((void **)arg);

	if (len == 1)
		ft_printf("\n");
	else
	{
		if (ft_strncmp(arg[1], "-n", 3) == 0)
			i++;
		while (i < len)
		{
			ft_printf("%s", arg[i]);
			i++;
		}
		if (ft_strncmp(arg[1], "-n", 3) != 0)
			ft_printf("\n");

	}
}

void		comm_pwd(char **arg, int map_i)
{
	int arg_len;

	arg_len = ft_arraylen((void **)arg);
	if (arg_len == 1)
	{
		update_pwd();
		ft_printf("%s\n", g_sh.pwd);
	}
	else
		print_error("too many arguments", 1);	
}

void		comm_cd(char **arg, int map_i)
{
	return ;
}

void		comm_export(char **arg, int map_i)
{
	return ;
}

void		comm_unset(char **arg, int map_i)
{
	return ; 
}

void		comm_env(char **arg, int map_i)
{
	return ;
}


void		comm_sh(char **arg, int map_i)
{	
	// char	**arg;
	//pid_t	pid;
	// t_list 	*lstptr;

	//char	*argv2[] = {"/bin/echo", "hello  > text", NULL};
	// lstptr = g_sh.map[map_i];

	// arg = create_arg(&lstptr);
	// if  (g_sh.error)
	// 	return ;
	// pid = fork();
	// if (pid == 0)
	// {
	execve(arg[0], arg, g_sh.env);
	// }
	// else if (pid < 0)
	// 	print_error("failed to create a new process");
	// wait(&pid);
	//ft_printf("%d\n", ft_strarraylen(argv));
	//ft_strarr_free(arg);
	
}

char	*between_quotes(char *str, t_list **lstptr)
{
	char *tmp;
	int qt;

	qt = (*lstptr)->ctg;
	*lstptr = (*lstptr)->next;
	while (*lstptr && (*lstptr)->ctg != qt)
	{
		if ((*lstptr)->ctg == SP)
		{
			while ((*lstptr)->atr-- > 0)
				str = ft_straddchr_free(str, ' ');
		}
		else
		{
			tmp = str;
			str = ft_strjoin(str, (*lstptr)->content);
			free(tmp);
		}
		*lstptr = (*lstptr)->next;
	}
	//*lstptr = (*lstptr == NULL) ? NULL : (*lstptr)->next;
	g_sh.flag = 0;
	return (str);
}

void redirection_sign(t_list **lstptr)
{
	if ((*lstptr)->ctg == GR_SIGN)
		g_sh.rewrite = 1;
	//*lstptr = (*lstptr)->next;
	if (!((*lstptr)->next))
	{
		print_error("syntax error near unexpected token 'newline'", 1);
		return ;
	}
	if (g_sh.redirect)
		free(g_sh.redirect);
	g_sh.redirect = ft_strdup((*lstptr)->next->content);
	//*lstptr = (*lstptr)->next;
}

char **create_strarray_comm(t_list **lstptr)
{
	char **arr;

	arr = malloc(sizeof(char *) * 2);
	arr[0] = ft_strdup((*lstptr)->content);	
	arr[1] = NULL;
	*lstptr = (*lstptr)->next;
	return (arr);
}

char 	**add_to_arg_flag(char **arr, t_list **lstptr)
{

	arr = add_elem_to_arr(arr, (*lstptr)->content, NULL);
	*lstptr = (*lstptr)->next;
	return (arr);
}

// void	check_rest_lst(t_list **lstptr)
// {
// 	if (!(*lstptr))
// 		return (NULL);
// 	if ((*lstptr)->ctg == SP)
// 		*lstptr = (*lstptr)->next;
// 	if ((*lstptr)->ctg == COMM)
// 		*lstptr = (*lstptr)->next;
// 	}
// }

char	*strjoin_free(char *s1, char *s2)
{
	char *tmp;

	tmp = s1;

	s1 = ft_strjoin(s1, s2);
	free(tmp);
	return (s1);
}

char 	**add_to_arg_else(char **arr, t_list **lstptr)
{
	char *str;

	str = NULL;
	while ((*lstptr) && (*lstptr)->ctg != PIPE)
	{
		if ((*lstptr)->ctg == DB_QT || (*lstptr)->ctg == SN_QT)
			str = between_quotes(str, lstptr);
		else if ((*lstptr)->ctg == SP)
			str = ft_straddchr_free(str, ' ');
		else if ((*lstptr)->ctg == GR_SIGN || (*lstptr)->ctg == DB_GR_SIGN ||
			(*lstptr)->ctg == LESS_SIGN)
		{
			*lstptr = (*lstptr)->next;
			// if ((*lstptr)->ctg == SP)
			// 	*lstptr = (*lstptr)->next;
		}
		else
			str = strjoin_free(str, (*lstptr)->content);
		*lstptr = (*lstptr == NULL) ? NULL : (*lstptr)->next;
	}
	arr = add_elem_to_arr(arr, str, NULL);
	g_sh.flag = 0;
	return (arr);
}

char **create_arg(t_list *lstptr)
{
	char	**arr;

	arr = create_strarray_comm(&lstptr);
	while (lstptr && lstptr->ctg != PIPE)
	{
		if (lstptr->ctg == SP)
			lstptr = lstptr->next;
		if (lstptr == NULL)
			break ;
		if (lstptr->ctg == FLAG && g_sh.flag)
			arr = add_to_arg_flag(arr, &lstptr);
		// else if ((*lstptr)->ctg == DB_QT || (*lstptr)->ctg == SN_QT)
		// 	arr = between_quotes(arr, lstptr);
		// else if ((*lstptr)->ctg == GR_SIGN || (*lstptr)->ctg == DB_GR_SIGN ||
		// 	(*lstptr)->ctg == LESS_SIGN || (*lstptr)->ctg == COMM)
		// {
		// 	*lstptr = (*lstptr)->next;
		// }
		else
			arr = add_to_arg_else(arr, &lstptr);
	}
	return (arr);
}

/*
** Checks existing system executable for the argument
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

/*
** Checks builtin commands and existing system executable for the argument
*/

t_comm		check_builtins_and_bin(char *comm)
{
	if (ft_strnequ_alpha(comm, "exit", 5) == 0)
		g_sh.exit = 1;
	else if (ft_strnequ_alpha(comm, "echo", 5) == 0)
		return (ECHO);
	else if (ft_strnequ_alpha(comm, "pwd", 4) == 0)
		return (PWD);
	else if (ft_strnequ_alpha(comm, "cd", 3) == 0)
		return (CD);
	else if (ft_strnequ_alpha(comm, "export", 7) == 0)
		return (EXPORT);
	else if (ft_strnequ_alpha(comm, "unset", 6) == 0)
		return (UNSET);
	else if (ft_strnequ_alpha(comm, "env", 4) == 0)
		return (ENV);
	else if (check_bin(comm))
		return (SH);
	else
		return (NOCOMM);
	return (VOID);
}

/*
** 
*/



void	output_redir(t_list *lst)
{
	if (lst->ctg == GR_SIGN)
		g_sh.fd[1] = open(lst->content, (O_CREAT | O_WRONLY | O_TRUNC), 0666);
	else if (lst->ctg == DB_GR_SIGN)
		g_sh.fd[1] = open(lst->content, (O_CREAT | O_WRONLY | O_APPEND), 0666);
	if (g_sh.fd[1] < 0)
	{
		print_error(strerror(errno), errno);
		return ;
	}
	if((dup2(g_sh.fd[1], 1)) < 0)
	{
		
		print_error(strerror(errno), errno);
		return ;
		
	}
}

void	restore_fd()
{
	if (g_sh.fd[0])
	{
		close(g_sh.fd[0]);
		if ((dup2(0, g_sh.fd[2])) < 0)
		{
			print_error(strerror(errno), errno);
			return ;
		}
	}
	if (g_sh.fd[1])
	{
		close(g_sh.fd[1]);
		g_sh.fd[1] = 0;
		close(1);
		if ((dup2(g_sh.fd[3], 1)) < 0)
		{
			print_error(strerror(errno), errno);
			return ;
		}
	}
}

void 	set_fd()
{
	t_list *lst;

	
	if (g_sh.map_i + 1 < g_sh.map_len)
	{
		lst = g_sh.map[g_sh.map_i + 1];
		if (lst->ctg == GR_SIGN || lst->ctg == DB_GR_SIGN)
			output_redir(lst);
	}
}

void	exec()
{
	static void		(*exec_comm[])(char **arg, int) = {comm_void, comm_echo, comm_pwd,
					comm_cd, comm_export, comm_unset, comm_env, comm_sh, comm_void};
	pid_t			pid;
	char			buff;
	char			**arg;
	t_list 			*lstptr;

	if (pipe(g_sh.p) < 0)
		exit (1);
	lstptr = g_sh.map[g_sh.map_i];
	arg = create_arg(g_sh.map[g_sh.map_i]);
	pid = fork();
	if (pid == 0)
	{
		exec_comm[g_sh.map[g_sh.map_i]->comm](arg, g_sh.map_i);
		close(g_sh.p[0]);
		write(g_sh.p[1], &g_sh.status[0], 1);
		exit(0);
	}
	else if (pid < 0)
		print_error("failed to create a new process", 1);
	close(g_sh.p[1]);
	wait(&pid);
	read(g_sh.p[0], &g_sh.status[0], 1);
	ft_strarr_free(arg);
}

void	exec_input(void)
{
	int				i;

	i = 0;	
	while (g_sh.input_tab[i])
	{
		parser(g_sh.input_tab[i]);
		g_sh.map_len = ft_arraylen((void **) g_sh.map);
		if (g_sh.error)
			return ;
		//if (g_sh.map_len > 1)
		while (g_sh.map_i < g_sh.map_len)
		{
			set_fd();
			if (g_sh.exit)
				exit_shell(errno);
			exec();
			restore_fd();
			g_sh.map_i++;
		}
		clear_tokens();
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
		clear_shell();
	}
	ft_strarr_free(g_sh.env);
	return (0);
}
