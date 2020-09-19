/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ_alpha.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:58:16 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/18 17:00:49 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ_alpha(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (ft_tolower(s1[i]) != ft_tolower(s2[i]))
			return (1);
		i++;
	}
	return (0);
}
