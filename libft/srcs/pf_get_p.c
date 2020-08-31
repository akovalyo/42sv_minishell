/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_get_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 09:55:15 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/13 11:23:08 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		precis_px(t_printf *flags, char *str)
{
	if (flags->precis_minus && flags->precis_val > 0)
	{
		if (flags->sp == 5)
			putstr_count(flags, "0x");
		putstr_diu_count(flags, str);
		while (flags->precis_val > flags->s_len)
		{
			putchar_count(flags, ' ');
			flags->precis_val--;
			return (1);
		}
	}
	else if (flags->s_len < flags->precis_val)
	{
		flags->precis_val = flags->precis_val - flags->s_len;
		if (flags->sp == 5)
			flags->precis_val += 2;
		flags->width_val = flags->width_val - flags->s_len - flags->precis_val;
		flags->print_precis = 1;
	}
	return (0);
}

void	width_px(t_printf *flags, char *str)
{
	if (!flags->print_precis)
		flags->width_val -= flags->s_len;
	if (flags->precis && !flags->precis_val && str[0] == '0'
				&& !flags->print_precis)
		flags->width_val++;
	print_width(flags, ' ');
	if (flags->sp == 5)
		putstr_count(flags, "0x");
	if (flags->print_precis)
		print_precis_diu(flags);
	putstr_diu_count(flags, str);
}

void	zero_px(t_printf *flags, char *str)
{
	if (!flags->print_precis)
		flags->width_val -= flags->s_len;
	if (flags->precis && flags->precis_val == 0 && str[0] == '0'
				&& !flags->print_precis)
		flags->width_val++;
	if (flags->precis)
	{
		print_width(flags, ' ');
		if (flags->sp == 5)
			putstr_count(flags, "0x");
		if (flags->print_precis)
			print_precis_diu(flags);
	}
	else
	{
		if (flags->sp == 5)
			putstr_count(flags, "0x");
		print_width(flags, '0');
	}
	putstr_diu_count(flags, str);
}

void	minus_px(t_printf *flags, char *str)
{
	if (!flags->print_precis)
		flags->width_val -= flags->s_len;
	if (flags->precis && flags->precis_val == 0 && str[0] == '0'
				&& !flags->print_precis)
		flags->width_val++;
	if (flags->sp == 5)
		putstr_count(flags, "0x");
	if (flags->print_precis)
		print_precis_diu(flags);
	putstr_diu_count(flags, str);
	print_width(flags, ' ');
}

void	get_p(t_printf *flags, va_list *ap)
{
	char *str;

	str = conv_base_uns(va_arg(*ap, size_t), 16, 0);
	flags->s_len = ft_strlen(str) + 2;
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
		putstr_count(flags, "0x");
		if (flags->print_precis)
			print_precis_diu(flags);
		putstr_diu_count(flags, str);
	}
	ft_strdel(&str);
	clear_flags(flags);
}
