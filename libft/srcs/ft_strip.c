/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:47:47 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/16 16:36:15 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strip(char *str)
{
	int		start;
	int		end;
	char	*new;

	if (!str)
		return (NULL);
	start = 0;
	end = ft_strlen(str);
	end = end > 0 ? end - 1 : 0;
	if (end == 0)
		return (ft_strnew(0));
	while (ft_isspace(str[start]))
		start++;
	while (ft_isspace(str[end]))
		end--;
	if (!(new = ft_strsub(str, start, end - start + 2)))
		return (NULL);
	return (new);
}
