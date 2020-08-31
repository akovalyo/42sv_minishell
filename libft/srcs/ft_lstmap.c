/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 20:41:34 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/20 15:51:01 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;
	t_list *elem;

	if (!lst)
		return (NULL);
	if (!(elem = ft_lstnew(f(lst->content))))
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		if (!(new = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&elem, del);
			return (NULL);
		}
		ft_lstadd_back(&elem, new);
		lst = lst->next;
	}
	return (elem);
}
