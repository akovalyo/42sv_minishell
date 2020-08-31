/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 14:40:52 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/05 15:26:21 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_long(long nbr)
{
	char	*tmp;
	char	*res;

	res = NULL;
	if (nbr < 0)
	{
		tmp = ft_itoa_uns(-nbr);
		res = ft_strjoin("-", tmp);
		ft_strdel(&tmp);
	}
	else
		res = ft_itoa_uns(nbr);
	return (res);
}
