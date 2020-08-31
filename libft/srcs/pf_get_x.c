/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_get_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 12:16:43 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/13 11:23:25 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	get_x(t_printf *flags, va_list *ap)
{
	char *str;

	if (flags->sp == 7)
		str = conv_base(va_arg(*ap, int), 16, 1);
	else
		str = conv_base(va_arg(*ap, int), 16, 0);
	flags->s_len = ft_strlen(str);
	if (flags->precis && precis_px(flags, str))
		return ;
	if (flags->width && !flags->minus && !flags->zero)
		width_px(flags, str);
	else if (flags->zero && !flags->minus)
		zero_px(flags, str);
	else if (flags->minus)
		minus_px(flags, str);
	else
	{
		if (flags->print_precis)
			print_precis_diu(flags);
		putstr_diu_count(flags, str);
	}
	ft_strdel(&str);
	clear_flags(flags);
}
