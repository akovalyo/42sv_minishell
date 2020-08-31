/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_get_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 08:57:32 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/13 11:23:20 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	get_u(t_printf *flags, va_list *ap)
{
	char *str;

	str = ft_itoa_uns(va_arg(*ap, unsigned int));
	flags->s_len = ft_strlen(str);
	if (flags->precis && precis_diu(flags, str))
		return ;
	if (flags->width && !flags->minus && !flags->zero)
		width_diu(flags, str);
	else if (flags->zero && !flags->minus)
		zero_diu(flags, str);
	else if (flags->minus)
		minus_diu(flags, str);
	else
	{
		if (flags->print_precis)
			print_precis_diu(flags);
		putstr_diu_count(flags, str);
	}
	ft_strdel(&str);
	clear_flags(flags);
}
