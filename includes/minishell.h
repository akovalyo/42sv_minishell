/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:45:10 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/25 15:49:14 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "libft.h"
# define RESERVED "<>:\"/\\|&*"

typedef enum		e_comm
{
	ECHO = 1, PWD, CD, EXPORT, UNSET, ENV, SH
}					t_comm;

typedef struct		s_shell
{
	char			**env;
	char			*input;
	char			**input_tab;
	char			*pwd;
	int				sn_qt;
	int				db_qt;
	int				exit : 1;
	t_comm			comm;
	int				n : 1;
	short			flags;
	int				fl_ignore : 1;
	t_list			*pars;

}                   t_shell;

/*
** global variables
*/

t_shell				g_sh;

/*
** main.c
*/

void				exit_shell(char *message);
char				**read_input();
void				comm_void(char **tab_comm);
void				comm_echo(char **tab_comm);
void				comm_pwd(char **tab_comm);
void				comm_cd(char **tab_comm);
void				comm_export(char **tab_comm);
void				comm_unset(char **tab_comm);
void				comm_env(char **tab_comm);
void				comm_sh(char **tab_comm);
int 				check_bin(char *comm);
char				*get_env(char *var);
void				check_builtins_and_bin(char **tab_comm);
char				**parse_cmd(char *comm);
void				check_comm_line(char **tab_comm);
void				exec_input();
int 				special_char(char c);



/*
** signal.c
*/

void				update_pwd();
void				sig_func(int sig);
void				sig_sl(int sig);

/*
** utils.c
*/

void				clear_scr(void);
void				init_shell();
void				clear_shell();
void				prompt_msg();

/*
** memory.c
*/

char				**arr_realloc(char **arr, int size);
void				free_pars();

/*
** env.c
*/

void				init_env(char **env);
int					addnode_envv(char *arg, int i);
char				*get_env(char *var);

#endif