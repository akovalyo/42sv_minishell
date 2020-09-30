/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:55:46 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/29 16:38:56 by akovalyo         ###   ########.fr       */
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
		exit_shell("read error");
	else if (ret == 0)
		exit_shell(NULL);
	tab_input = ft_strsplit(g_sh.input, ';');
	free(g_sh.input);
	g_sh.input = NULL;
	return (tab_input);
}

void	comm_void(void)
{
	if (g_sh.comm == VOID)
		ft_printf("");
	else if (g_sh.comm == NOCOMM)
		ft_printf("minishell: command not found: %s\n", g_sh.tokens->content);
}

void		comm_echo(void)
{
	int i;
	int len;

	i = 0;
	// if (ft_arraylen(tab_comm) == 1)
	// 	ft_printf("\n");
	// else
	// {
	// 	len = ft_strlen(tab_comm[1]);
	// 	if (ft_strncmp(tab_comm[1], "-n ", 3) == 0)
	// 	{
	// 		//g_sh.n = 1;
	// 		i = 3;
	// 	}
	// 	while (i < len)
	// 	{

	// 	}
	// 	ft_printf("%s\n", tab_comm[1]);
	// }
}

void		comm_pwd(void)
{
	if (g_sh.tokens->next == NULL || (ft_lstsize(g_sh.tokens) == 2 && g_sh.tokens->next->ctg == SP))
	{
		update_pwd();
		ft_printf("%s\n", g_sh.pwd);
	}
	else
		ft_printf("minishell: too many arguments\n");	
}

void		comm_cd(void)
{
	return ;
}

void		comm_export(void)
{
	return ;
}

void		comm_unset(void)
{
	return ; 
}

void		comm_env(void)
{
	return ;
}

void		comm_sh(void)
{	
	char	**arg;
	pid_t	pid;
	t_list 	*lstptr;
	//char	*argv2[] = {"/bin/echo", "hello  > text", NULL};
	lstptr = g_sh.tokens;

	arg = create_arg(&lstptr);
	
	pid = fork();
	if (pid == 0)
	{
		if (g_sh.error)
			exit(0);
		execve(arg[0], arg, g_sh.env);
	}
	else if (pid < 0)
		ft_printf("minishell: failed to create a new process\n");
	wait(&pid);
	//ft_printf("%d\n", ft_strarraylen(argv));
	ft_strarr_free(arg);
	
}

char	**between_quotes(char **arr, t_list **lstptr)
{
	char *new;
	char *tmp;
	int qt;

	new = NULL;
	qt = (*lstptr)->ctg;
	*lstptr = (*lstptr)->next;
	while (*lstptr && (*lstptr)->ctg != qt)
	{
		if ((*lstptr)->ctg == SP)
		{
			while ((*lstptr)->atr-- > 0)
				new = ft_straddchr_free(new, ' ');
		}
		else
		{
			tmp = new;
			new = ft_strjoin(new, (*lstptr)->content);
			free(tmp);
		}
		*lstptr = (*lstptr)->next;
	}
	*lstptr = (*lstptr == NULL) ? NULL : (*lstptr)->next;
	g_sh.flag = 0;
	return (add_elem_to_arr(arr, new, free));
}

void redirection_sign(t_list **lstptr)
{
	if ((*lstptr)->ctg == GR_SIGN)
		g_sh.rewrite = 1;
	//*lstptr = (*lstptr)->next;
	if (!((*lstptr)->next))
	{
		g_sh.error = ft_strdup("minishell: syntax error near unexpected token 'newline'");
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

char 	**add_to_arg_else(char **arr, t_list **lstptr)
{

	arr = add_elem_to_arr(arr, (*lstptr)->content, NULL);
	*lstptr = (*lstptr)->next;
	g_sh.flag = 0;
	return (arr);
}

char **create_arg(t_list **lstptr)
{
	char	**arr;

	arr = create_strarray_comm(lstptr);
	while (*lstptr)
	{
		if ((*lstptr)->ctg == SP)
			*lstptr = (*lstptr)->next;
		if ((*lstptr)->ctg == FLAG && g_sh.flag)
			arr = add_to_arg_flag(arr, lstptr);
		else if ((*lstptr)->ctg == DB_QT || (*lstptr)->ctg == SN_QT)
			arr = between_quotes(arr, lstptr);
		else if (((*lstptr)->ctg == GR_SIGN || (*lstptr)->ctg == DB_GR_SIGN) && (*lstptr)->atr == g_sh.red_count)
		{
			redirection_sign(lstptr);
			return (arr);
		}
		else
			arr = add_to_arg_else(arr, lstptr);
	}
	return (arr);
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

void		check_builtins_and_bin(char *comm)
{
	if (ft_strnequ_alpha(comm, "exit", 5) == 0)
		g_sh.exit = 1;
	else if (ft_strnequ_alpha(comm, "echo", 5) == 0)
		g_sh.comm = ECHO;
	else if (ft_strnequ_alpha(comm, "pwd", 4) == 0)
		g_sh.comm = PWD;
	else if (ft_strnequ_alpha(comm, "cd", 3) == 0)
		g_sh.comm = CD;
	else if (ft_strnequ_alpha(comm, "export", 7) == 0)
		g_sh.comm = EXPORT;
	else if (ft_strnequ_alpha(comm, "unset", 6) == 0)
		g_sh.comm = UNSET;
	else if (ft_strnequ_alpha(comm, "env", 4) == 0)
		g_sh.comm = ENV;
	else if (check_bin(comm))
		g_sh.comm = SH;
	else
		g_sh.comm = NOCOMM;
	
}

/*
** 
*/

void	exec_input(void)
{
	int				i;
	//char			**tmp;
	int				ret;
	static void		(*exec_comm[])(void) = {comm_void, comm_echo, comm_pwd,
					comm_cd, comm_export, comm_unset, comm_env, comm_sh, comm_void};
	i = 0;
	
	while (g_sh.input_tab[i])
	{
		parser(g_sh.input_tab[i]);
		if (g_sh.exit)
		{
			exit_shell(NULL);
		}
		exec_comm[g_sh.comm]();
		ft_lstclear(&(g_sh.tokens), free);
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
		if (g_sh.error)
			ft_printf("%s\n", g_sh.error);
		clear_shell();
	}
	ft_strarr_free(g_sh.env);
	return (0);
}
