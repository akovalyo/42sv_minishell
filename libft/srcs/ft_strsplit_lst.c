/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 11:53:41 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/29 16:11:31 by akovalyo         ###   ########.fr       */
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
	char	**arr;
	t_list	*result;
	int		arr_len;
	int		i;

	result = NULL;
	arr = ft_strsplit(s, c);
	arr_len = ft_arraylen((void **)arr);
	i = 0;
	while (i < arr_len)
	{
		add_node(&result, arr[i]);
		i++;
	}
	ft_strarr_free(arr);
	return (result);
}
