/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 09:50:41 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/05 22:53:49 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct		s_printf
{
	const char		*specif;
	unsigned int	sp : 4;
	unsigned int	i;
	unsigned int	count;
	unsigned int	zero : 1;
	unsigned int	minus : 1;
	unsigned int	width : 1;
	int				width_val;
	unsigned int	precis : 1;
	int				precis_val;
	unsigned int	precis_minus : 1;
	int				s_len;
	unsigned int	print_precis : 1;
	unsigned int	dig_minus : 1;
}					t_printf;

typedef void		t_conv(t_printf *flags, va_list *ap);

/*
** get
*/

void				get_c(t_printf *flags, va_list *ap);
void				print_minus_c(t_printf *flags, char ch);
void				print_c(t_printf *flags, char ch, char fill);
int					precis_c(t_printf *flags, char ch);
void				get_s(t_printf *flags, va_list *ap);
void				width_s(t_printf *flags, char *str);
void				zero_minus_s(t_printf *flags, char *str);
void				precis_s(t_printf *flags, char **str);
void				print_precis_s(t_printf *flags, char **str);
void				get_di(t_printf *flags, va_list *ap);
void				zero_diu(t_printf *flags, char *str);
void				minus_diu(t_printf *flags, char *str);
void				width_diu(t_printf *flags, char *str);
int					precis_diu(t_printf *flags, char *str);
void				get_u(t_printf *flags, va_list *ap);
void				get_p(t_printf *flags, va_list *ap);
int					precis_px(t_printf *flags, char *str);
void				width_px(t_printf *flags, char *str);
void				zero_px(t_printf *flags, char *str);
void				minus_px(t_printf *flags, char *str);
void				get_x(t_printf *flags, va_list *ap);

/*
** analyse.c
*/

void				analyse_flags(t_printf *flags, const char *str);
void				analyse_precis(t_printf *flags, const char *str);
void				analyse_width(t_printf *flags, const char *str);

/*
** asterisk.c
*/

void				analyse_asterisk(t_printf *flags, const char *str,
									va_list *ap);
void				asterisk_width(t_printf *flags, va_list *ap);
void				asterisk_precis(t_printf *flags, va_list *ap);

/*
** helpers.c
*/

int					hex_ascii(size_t n, int letter);
char				*conv_base(unsigned int nbr, unsigned int base, int letter);
char				*conv_base_uns(size_t nbr, int base, char letter);
char				*strdup_printf(const char *s);

/*
** print.c
*/

void				print_precis_diu(t_printf *flags);
void				print_width(t_printf *flags, char fill);
void				putchar_count(t_printf *flags, char c);
void				putstr_count(t_printf *flags, char *str);
void				putstr_diu_count(t_printf *flags, char *str);

/*
** checker.c
*/

void				format_checker(t_printf *flags, const char *str,
									va_list *ap);
int					specifier_checker(t_printf *flags, const char *str);

/*
** ft_printf.c
*/

int					ft_printf(const char *format, ...);
void				init_flags(t_printf *flags);
void				clear_flags(t_printf *flags);

#endif
