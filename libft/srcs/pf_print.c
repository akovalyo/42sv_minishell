/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 11:01:09 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/13 11:23:38 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_width(t_printf *flags, char fill)
{
	while (flags->width_val > 0)
	{
		putchar_count(flags, fill);
		flags->width_val--;
	}
}

void	print_precis_diu(t_printf *flags)
{
	while (flags->precis_val > 0)
	{
		putchar_count(flags, '0');
		flags->precis_val--;
	}
}

void	putchar_count(t_printf *flags, char ch)
{
	ft_putchar(ch);
	flags->count++;
}

void	putstr_count(t_printf *flags, char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			putchar_count(flags, str[i]);
			i++;
		}
	}
}

void	putstr_diu_count(t_printf *flags, char *str)
{
	int i;

	i = 0;
	if (flags->precis && !flags->precis_val && !flags->print_precis
				&& str[0] == '0')
		return ;
	if (str)
	{
		while (str[i])
		{
			putchar_count(flags, str[i]);
			i++;
		}
	}
}
