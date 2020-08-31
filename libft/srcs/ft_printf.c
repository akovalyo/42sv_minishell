/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 10:40:44 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/05 22:56:31 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

void	init_flags(t_printf *flags)
{
	flags->specif = "diuscpxX%";
	flags->sp = 10;
	flags->i = 0;
	flags->count = 0;
	flags->zero = 0;
	flags->minus = 0;
	flags->width = 0;
	flags->width_val = 0;
	flags->precis = 0;
	flags->precis_val = 0;
	flags->precis_minus = 0;
	flags->s_len = 0;
	flags->print_precis = 0;
	flags->dig_minus = 0;
}

void	clear_flags(t_printf *flags)
{
	flags->sp = -1;
	flags->zero = 0;
	flags->minus = 0;
	flags->width = 0;
	flags->width_val = 0;
	flags->precis = 0;
	flags->precis_val = 0;
	flags->precis_minus = 0;
	flags->s_len = 0;
	flags->print_precis = 0;
	flags->dig_minus = 0;
}

int		ft_printf(const char *format, ...)
{
	va_list			ap;
	t_printf		flags;
	static t_conv	*fn_array[] = {get_di, get_di, get_u, get_s, get_c,
								get_p, get_x, get_x, get_c};

	init_flags(&flags);
	va_start(ap, format);
	while (format[flags.i])
	{
		if (format[flags.i] != '%')
		{
			putchar_count(&flags, format[flags.i]);
			flags.i++;
		}
		else
		{
			flags.i++;
			format_checker(&flags, format, &ap);
			if (specifier_checker(&flags, format))
				fn_array[flags.sp](&flags, &ap);
			flags.i = (format[flags.i]) ? (flags.i + 1) : flags.i;
		}
	}
	va_end(ap);
	return (flags.count);
}
