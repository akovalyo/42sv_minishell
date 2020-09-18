/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:45:10 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/18 13:00:27 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define ECHO 1
# define PWD 2
# define CD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define CMD 10

# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include "libft.h"

typedef struct		s_shell
{
	char			**env;
	char			*input;
	char			**input_tab;
	char			*pwd;
	int				single_qt : 1;
	int				double_qt : 1;
	int				exit : 1;
	int				comm : 4;
	int				n : 1;

}                   t_shell;

// typedef struct		s_shlist
// {
// 	int				id;

// }					t_shlist;

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
void				check_builtins(char **tab_comm);
char				**parse_cmd(char *comm);
void				check_comm_line(char **tab_comm);
void				exec_input();
void				init_env(char **env);



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

#endif