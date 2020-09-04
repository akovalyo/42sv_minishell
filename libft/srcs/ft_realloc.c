/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 12:11:00 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/04 12:32:39 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	new = ft_memalloc(size);
	if (ptr != NULL)
	{
		new = ft_memcpy(new, ptr, size);
		free(ptr);
	}
	return (new);
}
