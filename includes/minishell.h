/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:45:10 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/29 11:27:39 by akovalyo         ###   ########.fr       */
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
	VOID, ECHO, PWD, CD, EXPORT, UNSET, ENV, SH, NOCOMM
}					t_comm;

typedef struct		s_shell
{
	char			**env;
	char			*input;
	char			**input_tab;
	char			*pwd;
	char			*error;
	int				sn_qt;
	int				db_qt;
	int				exit : 1;
	t_comm			comm;
	int				n_comm : 8;
	int				flag : 1;
	int				fl_ignore : 1;
	t_list			*tokens;
	char			*redirect;
	int				rewrite : 1;
	int				red_count;

}                   t_shell;

/*
** global variables
*/

t_shell				g_sh;

/*
** main.c
*/

char				**read_input(void);
void				comm_void(void);
void				comm_echo(void);
void				comm_pwd(void);
void				comm_cd(void);
void				comm_export(void);
void				comm_unset(void);
void				comm_env(void);
void				comm_sh(void);
char				**between_quotes(char **arr, t_list **lstptr);
void 				redirection_sign(t_list **lstptr);
char 				**create_strarray_comm(t_list **lstptr);
char 				**add_to_arg_flag(char **arr, t_list **lstptr);
char 				**add_to_arg_else(char **arr, t_list **lstptr);
char 				**create_arg(t_list **lstptr);
int 				check_bin(char *comm);
void				check_builtins_and_bin(char *comm);
void				exec_input(void);

/*
** signal.c
*/


void				sig_func(int sig);
void				sig_sl(int sig);

/*
** utils_1.c
*/

void				clear_scr(void);
void				init_shell(void);
void				clear_shell(void);
void				update_pwd(void);
void				prompt_msg(void);

/*
** utils_2.c
*/

int 				special_char(char c);
int 				isquote(char c);

/*
** memory.c
*/

char				**add_elem_to_arr(char **arr, char *str, void (*del)(void *));
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

void				addnode_comm(char *comm);
int					addnode_flags(char *arg, int i);
int					addnode_envv(char *arg, int i);
int					addnode_tilde(char *arg, int i);
int					addnode_str(char *arg, int i);


/*
** addnode_2.c
*/

int					addnode_spaces(char *arg, int i);
t_list 				*specialch_create_node(char *arg, int i);
int					addnode_specialch(char *arg, int i);

#endif