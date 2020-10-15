/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:45:10 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/14 17:22:09 by akovalyo         ###   ########.fr       */
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
# define RESERVED "<>:\"\'/\\|&*"

typedef struct		s_shell
{
	t_list			*tokens;
	t_list			**map;
	int				fdio[2];
	int				**gfd;
	char			**env;
	char			*input;
	char			**input_tab;
	int				error;
	int				exit : 1;
	int				flag : 1;
	int				fl_ignore : 1;
	int				n_comm : 8;
	int				sn_qt;
	int				db_qt;
	int				red_count;
	int				map_i;
	int				map_len;
	int				status[2];
}					t_shell;

/*
** global variables
*/

t_shell				g_sh;

/*
** addtoken_1.c
*/

int					addtoken_comm(char *str, int i);
int					addtoken_flags(char *str, int i);
int					addtoken_envv(char *str, int i);
int					addtoken_tilde(char *str, int i);
int					addtoken_str(char *str, int i);

/*
** addtoken_2.c
*/

int					addtoken_spaces(char *str, int i);
int					addtoken_specialch(char *str, int i);
int					addtoken_betweenq(char *str, int i);
int					addtoken_redir(char *str, int i);
int					addtoken_status(int i);

/*
** builtin_cd.c
*/

void				cd_home(void);
char				*cd_above_2(char **pwd_split, int len);
void				cd_above(void);
void				cd(char *path);
void				comm_cd(char **argv);

/*
** builtin_envmanage.c
*/

void				get_key_value(char *arg, char **key, char **value);
void				declare_env(void);
void				comm_export(char **argv);
void				comm_unset(char **argv);

/*
** builtins.c
*/

void				comm_echo(char **argv);
void				comm_pwd(char **argv);
void				comm_env(char **argv);

/*
** check_builtins_and_bin.c
*/

int					replace_content(t_list **node, char *cont, char **paths);
char				*create_path(char *bin, char *comm);
int					check_bin(t_list **node);
t_comm				check_builtins_and_bin(t_list **new);

/*
** comm_array.c
*/

char				**add_to_argv_comm(t_list **lstptr);
char				**add_to_arg_flag(char **arr, t_list **lstptr);
char				**add_elem_to_arr(char **arr, char *str,
						void (*del)(void *));
char				**add_to_argv_else(char **arr, t_list **lstptr);
char				**create_argv(t_list *lstptr);

/*
** env.c
*/

char				*get_envv(char *var);
int					get_envv_pos(char *var);
void				change_envv(char *key, char *value);
void				add_envv(char *key, char *value);
char				**remove_envv(int pos);

/*
** fd.c
*/

int					input_redir(int i, int j);
int					output_redir(int i, int j);
void				restore_fd(int i);
int					pipe_connect(int j);
void				set_fd(int j);

/*
** init.c
*/

void				set_fd_global(void);
void				init_env(char **env);
void				init_fd(void);
void				init_shell(void);

/*
** main.c
*/

void				comm_void(char **arg);
void				comm_sh(char **arg);
int					exec_comm(int j);
void				handle_input(void);
void				handle_input(void);

/*
** memory.c
*/

void				allocate_fd(void);
void				fd_free(void);
void				clear_inner(void);
void				exit_shell(int err);

/*
** parser.c
*/

char				*between_quotes(char *str, t_list **lstptr);
void				process_semicolons(char **str);
char				**read_input(void);
void				add_to_map(t_list *new);
void				parser(char *arg);

/*
** signal.c
*/

void				signal_in_parent(int sig);
void				signal_in_child(int sig);
void				signal_sl(int sig);
void				signal_parent(void);
void				signal_child(void);

/*
** utils_1.c
*/

void				clear_scr(void);
void				print_error(char *err, int err_n);
void				clear_shell(void);
char				*get_pwd(void);

/*
** utils_2.c
*/

int					special_char(char c);
int					isredir(char c);
int					isquote(char c);
int					is_redirect_ctg(t_list *lst);
int					skip_spaces(char *str, int i);

/*
** utils_addtoken.c
*/

int					handle_redir_sign(char *str, int *i);
t_list				*specialch_create_token(char *str, int i);
void				token_tilde_init(t_list **token);
int					isbetween_quotes(void);

/*
** utils_cd.c
*/

int					sh_chdir(char *path);
void				update_pwd_envv(void);
#endif
