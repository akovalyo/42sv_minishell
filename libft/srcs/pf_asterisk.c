/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_asterisk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 12:37:57 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/13 11:22:33 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	analyse_asterisk(t_printf *flags, const char *str, va_list *ap)
{
	if (str[flags->i - 1] == '%' || str[flags->i - 1] == '0' ||
			str[flags->i - 1] == '-')
		asterisk_width(flags, ap);
	if (str[flags->i - 1] == '.')
		asterisk_precis(flags, ap);
	flags->i++;
}

void	asterisk_precis(t_printf *flags, va_list *ap)
{
	flags->precis = 1;
	flags->precis_val = va_arg(*ap, int);
	if (flags->precis_val < 0)
		flags->precis = 0;
}

void	asterisk_width(t_printf *flags, va_list *ap)
{
	flags->width = 1;
	flags->width_val = va_arg(*ap, int);
	if (flags->width_val < 0)
	{
		flags->minus = 1;
		flags->width_val = -flags->width_val;
	}
}
