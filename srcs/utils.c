/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:29:13 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/14 11:23:09 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_scr(void)
{
	ft_printf("\e[1;1H\e[2J");
}

void	init_shell(t_shell *sh)
{
	sh->lines = NULL;
	sh->input = NULL;
	sh->single_qt = 0;
	sh->double_qt = 0;
	sh->exit = 0;
	sh->comm = 0;
	sh->n = 0;
	sh->arg_1 = 0;
}

void prompt_msg(void)
{
	char	buff[256];

	ft_printf("%s: ", getcwd(buff, 256));
}