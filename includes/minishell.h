/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:45:10 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/14 11:33:14 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define ECHO 1
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include "libft.h"

typedef struct      s_shell
{
    char            **lines;
    char            *input;
    int             single_qt : 1;
    int             double_qt : 1;
    int             exit : 1;
    int             comm : 4;
    int             n : 1;
    int             arg_1 : 1;

}                   t_shell;

/*
** main.c
*/

void	            exit_shell(t_shell *sh, char *message);
char	            **read_input(t_shell *sh);
void	            void_comm(t_shell *sh, char **tab_comm);
void	            echo_comm(t_shell *sh, char **tab_comm);
void	            check_builtins(t_shell *sh, char **tab_comm);
void	            parse_line(t_shell *sh, char **tab_comm);
void	            exec_lines(t_shell *sh);



/*
** signal.c
*/

void                sig_func(int sig);
void	            sig_sl(int sig);

/*
** utils.c
*/

void	            clear_scr(void);
void	            init_shell(t_shell *sh);
void                prompt_msg(void);

#endif