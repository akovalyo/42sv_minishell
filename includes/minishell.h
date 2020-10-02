/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:45:10 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/02 12:29:19 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "libft.h"
# define RESERVED "<>:\"/\\|&*"

typedef struct		s_shell
{
	t_list			*tokens;
	t_list			**map;
	int				fd[4];
	char			**env;
	char			*input;
	char			**input_tab;
	char			*pwd;
	char			*redirect;
	int				error;
	int				exit : 1;
	int				flag : 1;
	int				fl_ignore : 1;
	int				rewrite : 1;
	int				n_comm : 8;
	int				sn_qt;
	int				db_qt;
	int				red_count;	
	int				map_i;
	int				map_len;
	int				pipe;
	int				status[2];
	int				p[2];
}                   t_shell;

/*
** global variables
*/

t_shell				g_sh;

/*
** main.c
*/

void				add_to_map(t_list *new);


char				**read_input(void);
void				comm_void(char **arg, int map_i);
void				comm_echo(char **arg, int map_i);
void				comm_pwd(char **arg, int map_i);
void				comm_cd(char **arg, int imap_i);
void				comm_export(char **arg, int map_i);
void				comm_unset(char **arg, int map_i);
void				comm_env(char **arg, int map_i);
void				comm_sh(char **arg, int map_i);
char				*between_quotes(char *str, t_list **lstptr);
void 				redirection_sign(t_list **lstptr);
char 				**create_strarray_comm(t_list **lstptr);
char 				**add_to_arg_flag(char **arr, t_list **lstptr);
char 				**add_to_arg_else(char **arr, t_list **lstptr);
char 				**create_arg(t_list **lstptr);
int 				check_bin(char *comm);
t_comm				check_builtins_and_bin(char *comm);
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
int 				isredir(char c);

/*
** memory.c
*/

char				**add_elem_to_arr(char **arr, char *str, void (*del)(void *));
void				print_error(char *err, int err_n);
void 				clear_tokens(void);
void				exit_shell(int err);

/*
** env.c
*/

void				init_env(char **env);
int					addnode_envv(char *arg, int i);
char				*get_env(char *var);

/*
** parser.c
*/

int					skip_spaces(char *str, int i);
void				parser(char *arg);


/*
** addnode_1.c
*/

int					addnode_comm(char *str, int i);
int					addnode_flags(char *str, int i);
int					addnode_envv(char *str, int i);
int					addnode_tilde(char *str, int i);
int					addnode_str(char *str, int i);


/*
** addnode_2.c
*/

int					addnode_spaces(char *str, int i);
t_list 				*specialch_create_node(char *str, int i);
int					addnode_specialch(char *str, int i);
int					addnode_redir(char *str, int i);
int					addnode_status(char *str, int i);

#endif