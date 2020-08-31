/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_get_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 09:30:57 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/13 11:22:57 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		precis_c(t_printf *flags, char ch)
{
	if (flags->precis_minus && flags->precis_val > 0)
	{
		flags->precis_val--;
		putchar_count(flags, ch);
		while (flags->precis_val > 0)
		{
			putchar_count(flags, ' ');
			flags->precis_val--;
		}
		return (1);
	}
	return (0);
}

void	print_c(t_printf *flags, char ch, char fill)
{
	flags->width_val--;
	while (flags->width_val > 0)
	{
		putchar_count(flags, fill);
		flags->width_val--;
	}
	putchar_count(flags, ch);
}

void	print_minus_c(t_printf *flags, char ch)
{
	flags->width_val--;
	putchar_count(flags, ch);
	while (flags->width_val > 0)
	{
		putchar_count(flags, ' ');
		flags->width_val--;
	}
}

void	get_c(t_printf *flags, va_list *ap)
{
	char ch;

	if (flags->sp == 8)
		ch = '%';
	else
		ch = va_arg(*ap, int);
	if (flags->precis && precis_c(flags, ch))
		return ;
	if (flags->width && flags->width_val > 1)
	{
		if (flags->zero && !flags->minus)
			print_c(flags, ch, '0');
		else if (flags->minus)
			print_minus_c(flags, ch);
		else
			print_c(flags, ch, ' ');
	}
	else
		putchar_count(flags, ch);
	clear_flags(flags);
}
