/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 11:36:43 by akovalyo          #+#    #+#             */
/*   Updated: 2020/07/27 12:19:26 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	convert_ch(char c, int base, int *nbr)
{
	int		c_int;

	if (c >= '0' && c <= '9')
		c_int = c - '0';
	else if (c >= 'A' && c <= 'F')
		c_int = c - 'A' + 10;
	else if (c >= 'a' && c <= 'f')
		c_int = c - 'a' + 10;
	else
		return (0);
	if (c_int < base)
		*nbr = *nbr * base + c_int;
	else
		return (0);
	return (1);
}

static int	ft_atoi_cut(const char *nptr)
{
	int		collector;
	int		i;

	collector = 0;
	i = 0;
	while (nptr[i] == '\n' || nptr[i] == '\t' || nptr[i] == '\v' ||
			nptr[i] == '\r' || nptr[i] == '\f' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		collector = collector * 10 + nptr[i] - '0';
		i++;
	}
	return (collector);
}

int			ft_atoi_base_original(char *str, char *base)
{
	int	i;
	int	sign;
	int	nbr;
	int	int_base;

	int_base = ft_atoi_cut(base);
	if (!str || (int_base < 2 || int_base > 16))
		return (0);
	i = 0;
	nbr = 0;
	sign = 1;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v' ||
			str[i] == '\r' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = (str[i] == '-') ? -1 : 1;
		i++;
	}
	while (str[i] && convert_ch(str[i], int_base, &nbr))
		i++;
	return (nbr * sign);
}
