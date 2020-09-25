/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:54:52 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/25 11:09:36 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *fresh;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!(fresh = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	if (!s1)
		ft_strcpy(fresh, s2);
	else if (!s2)
		ft_strcpy(fresh, s1);
	else
	{
		ft_strcpy(fresh, s1);
		ft_strcat(fresh, s2);
	}
	return (fresh);
}
