/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddchr_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 10:08:28 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/25 12:33:42 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_straddchr_free(char *str, char ch)
{
	char	*new;
	size_t	len;

	len = 0;
	if (!ch && !str)
		return (NULL);
	if (str && !ch)
		return (str);
	else if (str)
	{
		len = ft_strlen(str);
		if (!(new = ft_strnew(len + 2)))
			return (NULL);
		ft_memmove(new, str, len);
		ft_strdel(&str);
	}
	else
		new = ft_strnew(2);
	new[len] = ch;
	return (new);
}
