/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:29:13 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/18 13:22:08 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Clears screen.
*/

void	clear_scr(void)
{
	ft_printf("\e[1;1H\e[2J");
}

/*
** Prints error and saves the error number to the 'g_sh'.
*/

void	print_error(char *err, int err_n)
{
	g_sh.error++;
	errno = err_n;
	ft_printf("minishell: %s\n", err);
}

/*
** Reinitializes the g_sh struct between user's input.
*/

void	clear_shell(void)
{
	clear_inner();
	ft_strarr_free(g_sh.input_tab);
	g_sh.input_tab = NULL;
	g_sh.sn_qt = 0;
	g_sh.db_qt = 0;
	g_sh.exit = 0;
	g_sh.n_comm = 0;
	g_sh.flag = 1;
}

/*
** Returns pointer to the value of the variable 'PWD'
*/

char	*get_pwd(void)
{
	char *pwd;

	if (!(pwd = get_envv("PWD")))
		return (NULL);
	return (pwd);
}
