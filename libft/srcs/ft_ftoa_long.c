/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 10:47:44 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/05 15:24:55 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*signific_handler(long double nbr, int precis, int *increment)
{
	size_t	signif;
	int		last;
	int		i;
	char	*mantis;

	i = 0;
	*increment = 0;
	mantis = ft_strnew(precis);
	while (i < precis + 1)
	{
		nbr *= 10;
		i++;
	}
	signif = (size_t)nbr;
	last = signif % 10;
	signif /= 10;
	signif = (last >= 5) ? signif + 1 : signif;
	if (ft_nbrlen(signif) > precis)
	{
		*increment = 1;
		ft_memset(mantis, '0', precis);
	}
	else
		mantis = ft_itoa_uns(signif);
	return (mantis);
}

char	*ft_ftoa_long(long double nbr, int precis, int sign)
{
	char	*str;
	size_t	int_part;
	int		point;
	int		increment;
	char	*signif;

	sign = (nbr < 0) ? 1 : 0;
	point = (precis) ? 1 : 0;
	nbr = sign ? -nbr : nbr;
	int_part = (size_t)nbr;
	nbr -= (size_t)int_part;
	str = ft_strnew(sign + ft_nbrlen(int_part) + point + precis);
	if (sign)
		ft_strcat(str, "-");
	signif = signific_handler(nbr, precis, &increment);
	int_part = increment ? int_part + 1 : int_part;
	ft_strcat(str, ft_itoa_uns(int_part));
	if (point)
	{
		ft_strcat(str, ".");
		ft_strcat(str, signif);
	}
	ft_strdel(&signif);
	return (str);
}
