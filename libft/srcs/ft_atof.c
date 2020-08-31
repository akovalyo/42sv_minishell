/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 09:24:46 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/20 10:07:56 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(char *nptr)
{
	float	val;
	float	signif;
	int		sign;

	val = 0;
	sign = 1;
	signif = 0.1;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
		val = 10 * val + *(nptr++) - '0';
	if (*nptr == '.')
	{
		nptr++;
		while (ft_isdigit(*nptr))
		{
			val += (*(nptr++) - '0') * signif;
			signif *= 0.1;
		}
	}
	return (val * sign);
}
