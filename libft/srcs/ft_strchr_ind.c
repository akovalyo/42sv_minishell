/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_ind.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 10:19:23 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/05 17:53:56 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_ind(const char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (i);
	return (10);
}
