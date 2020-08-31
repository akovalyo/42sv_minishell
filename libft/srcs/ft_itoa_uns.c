/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_uns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 10:54:56 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/05 15:26:46 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_uns(size_t nbr)
{
	char	*new;
	int		end;

	end = ft_nbrlen(nbr);
	new = (char *)malloc(sizeof(char) * end + 1);
	if (new == NULL)
		return (NULL);
	new[end] = '\0';
	end--;
	if (nbr == 0)
		new[end] = '0';
	while (nbr > 0)
	{
		new[end] = nbr % 10 + 48;
		nbr = nbr / 10;
		end--;
	}
	return (new);
}
