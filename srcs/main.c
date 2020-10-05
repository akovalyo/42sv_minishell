/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:55:46 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/05 16:37:19 by akovalyo         ###   ########.fr       */
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
	g_sh.flag = 0;
	return (str);
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

char	*strjoin_free(char *s1, char *s2)
{
	char *tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	free(tmp);
	return (s1);
}

char	*strtrim_free(char *s1)
{
	char *tmp;

	tmp = s1;
	s1 = ft_strtrim(s1);
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
			*lstptr = (*lstptr)->next;
		else
			str = strjoin_free(str, (*lstptr)->content);
		*lstptr = (*lstptr == NULL) ? NULL : (*lstptr)->next;
	}
	str = strtrim_free(str);
	arr = add_elem_to_arr(arr, str, free);
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

void		comm_sh(char **arg, int map_i)
{	
	pid_t	pid;
	pid = fork();
	if (pid < 0)
		print_error("failed to create a new process", 1);
	else if (pid == 0)
	{
		execve(arg[0], arg, g_sh.env);
	}
	else 
	{
		wait(&pid);
	}
}

void	exec(void)
{
	static void		(*exec_comm[])(char **arg, int) = {comm_void, comm_echo, comm_pwd,
					comm_cd, comm_export, comm_unset, comm_env, comm_void};
	char			buff;
	char			**arg;
	t_list 			*lstptr;

	lstptr = g_sh.map[g_sh.map_i];
	arg = create_arg(g_sh.map[g_sh.map_i]);

	if (g_sh.map[g_sh.map_i]->comm == SH)
		comm_sh(arg, g_sh.map_i);
	else
		exec_comm[g_sh.map[g_sh.map_i]->comm](arg, g_sh.map_i);
	ft_strarr_free(arg);
}

void increment_mapi(void)
{
	t_list *lst;
	
	if (g_sh.map_i + 1 < g_sh.map_len)
	{
		lst = g_sh.map[g_sh.map_i + 1];
		if (lst->ctg == GR_SIGN || lst->ctg == DB_GR_SIGN || lst->ctg == LESS_SIGN)
			g_sh.map_i += 2;
		else
			g_sh.map_i++;
	}
	else
		g_sh.map_i++;
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
		while (g_sh.map_i < g_sh.map_len)
		{
			set_fd();
			if (g_sh.exit)
				exit_shell(errno);
			exec();
			restore_fd();
			increment_mapi();
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
		ft_printf("%s: ", get_pwd());
		signal(SIGINT, sig_func);
		signal(SIGQUIT, sig_sl);
		g_sh.input_tab = read_input();
		exec_input();
		clear_shell();
	}
	ft_strarr_free(g_sh.env);
	return (0);
}
