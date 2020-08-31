/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_get_di.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 08:49:49 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/13 11:23:02 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		precis_diu(t_printf *flags, char *str)
{
	if (flags->precis_minus && flags->precis_val > 0)
	{
		putstr_diu_count(flags, str);
		while (flags->precis_val > flags->s_len)
		{
			putchar_count(flags, ' ');
			flags->precis_val--;
			return (1);
		}
	}
	else if ((flags->s_len - flags->dig_minus) < flags->precis_val)
	{
		flags->precis_val = flags->precis_val - flags->s_len + flags->dig_minus;
		flags->width_val = flags->width_val - flags->s_len - flags->precis_val;
		flags->print_precis = 1;
	}
	return (0);
}

void	width_diu(t_printf *flags, char *str)
{
	if (!flags->print_precis)
		flags->width_val -= flags->s_len;
	if (flags->precis && !flags->precis_val && str[0] == '0'
				&& !flags->print_precis)
		flags->width_val++;
	print_width(flags, ' ');
	if (flags->dig_minus)
		putchar_count(flags, '-');
	if (flags->print_precis)
		print_precis_diu(flags);
	(flags->dig_minus) ? putstr_diu_count(flags, &str[1]) :
				putstr_diu_count(flags, str);
}

void	zero_diu(t_printf *flags, char *str)
{
	if (!flags->print_precis)
		flags->width_val -= flags->s_len;
	if (flags->precis && flags->precis_val == 0 && str[0] == '0'
				&& !flags->print_precis)
		flags->width_val++;
	if (flags->precis)
	{
		print_width(flags, ' ');
		if (flags->dig_minus)
			putchar_count(flags, '-');
		if (flags->print_precis)
			print_precis_diu(flags);
	}
	else
	{
		if (flags->dig_minus)
			putchar_count(flags, '-');
		print_width(flags, '0');
	}
	(flags->dig_minus) ? putstr_diu_count(flags, &str[1]) :
				putstr_diu_count(flags, str);
}

void	minus_diu(t_printf *flags, char *str)
{
	if (!flags->print_precis)
		flags->width_val -= flags->s_len;
	if (flags->precis && flags->precis_val == 0 && str[0] == '0'
				&& !flags->print_precis)
		flags->width_val++;
	if (flags->dig_minus)
		putchar_count(flags, '-');
	if (flags->print_precis)
		print_precis_diu(flags);
	(flags->dig_minus) ? putstr_diu_count(flags, &str[1]) :
				putstr_diu_count(flags, str);
	print_width(flags, ' ');
}

void	get_di(t_printf *flags, va_list *ap)
{
	char *str;

	str = ft_itoa(va_arg(*ap, int));
	flags->dig_minus = (str[0] == '-') ? 1 : 0;
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
		if (flags->dig_minus)
			putchar_count(flags, '-');
		if (flags->print_precis)
			print_precis_diu(flags);
		(flags->dig_minus) ? putstr_diu_count(flags, &str[1]) :
				putstr_diu_count(flags, str);
	}
	ft_strdel(&str);
	clear_flags(flags);
}
