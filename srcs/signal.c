/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:22:19 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/05 16:36:02 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_func(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		ft_printf("%s: ", get_pwd());
		signal(SIGINT, sig_func);
	}
}

void	sig_sl(int sig)
{
	sig = 0;
	signal(SIGQUIT, sig_sl);
}
