/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 20:29:16 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/20 09:49:40 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *nptr)
{
	int					sign;
	unsigned long long	collector;
	int					i;

	sign = 1;
	collector = 0;
	i = 0;
	while (nptr[i] == '\n' || nptr[i] == '\t' || nptr[i] == '\v' ||
			nptr[i] == '\r' || nptr[i] == '\f' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		sign = (nptr[i] == '-') ? -1 : 1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		collector = collector * 10 + nptr[i] - '0';
		i++;
	}
	if (i > 19 || collector >= 9223372036854775808ULL)
		return (sign == 1 ? -1 : 0);
	return ((int)collector * sign);
}
