/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 11:53:41 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/22 12:27:35 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	add_node(t_list **result, char *str)
{
	t_list	*new;

	if (!(new = malloc(sizeof(t_list))))
		return ;
	new->content_size = ft_strlen(str);
	new->content = ft_strdup(str);
	new->next = NULL;
	ft_lstadd_back(result, new);
}

t_list		*ft_strsplit_lst(char const *s, char c)
{
	char	**tab;
	t_list	*result;
	int		tab_len;
	int		i;

	result = NULL;
	tab = ft_strsplit(s, c);
	tab_len = ft_strarraylen(tab);
	i = 0;
	while (i < tab_len)
	{
		add_node(&result, tab[i]);
		i++;
	}
	ft_strtab_free(tab);
	return (result);
}
