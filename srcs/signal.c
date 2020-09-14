/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:22:19 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/14 10:23:23 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_func(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		prompt_msg();
		signal(SIGINT, sig_func);
	}
}

void	sig_sl(int sig)
{
	sig = 0;
	signal(SIGQUIT, sig_sl);
}
