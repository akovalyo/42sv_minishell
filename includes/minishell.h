/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:45:10 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/27 21:13:31 by akovalyo         ###   ########.fr       */
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
	char			*redirect;
	int				rewrite : 1;

}                   t_shell;

/*
** global variables
*/

t_shell				g_sh;

/*
** main.c
*/

char				**read_input();
void				comm_void(char **tab_comm);
void				comm_echo(char **tab_comm);
void				comm_pwd(char **tab_comm);
void				comm_cd(char **tab_comm);
void				comm_export(char **tab_comm);
void				comm_unset(char **tab_comm);
void				comm_env(char **tab_comm);
void				comm_sh(char **tab_comm);
char				**between_quotes(char **arr, t_list **lstptr);
char 				**add_to_argv_rest(char **arr, t_list *lstptr);
char 				**create_argv(char **tab_comm);
int 				check_bin(char *comm);
void				check_builtins_and_bin(char **tab_comm);
char				**parse_cmd(char *comm);
void				exec_input();

/*
** signal.c
*/


void				sig_func(int sig);
void				sig_sl(int sig);

/*
** utils_1.c
*/

void				clear_scr(void);
void				init_shell();
void				clear_shell();
void				update_pwd();
void				prompt_msg();

/*
** utils_2.c
*/

int 				special_char(char c);
int 				isquote(char c);

/*
** memory.c
*/

char				**add_elem_to_arr(char **arr, char *str, int free_str);
void				exit_shell(char *message);

/*
** env.c
*/

void				init_env(char **env);
int					addnode_envv(char *arg, int i);
char				*get_env(char *var);

/*
** parser.c
*/

void				parser(char *arg);


/*
** addnode_1.c
*/

int					addnode_flags(char *arg, int i);
int					addnode_envv(char *arg, int i);
int					addnode_tilde(char *arg, int i);
int					addnode_str(char *arg, int i);
int					addnode_spaces(char *arg, int i);

/*
** addnode_2.c
*/

t_list 				*specialch_create_node(char *arg, int i);
int					addnode_specialch(char *arg, int i);

#endif