/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:01:24 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/18 17:19:09 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char const *s, char c)
{
	int i;
	int words;
	int found;

	i = 0;
	words = 0;
	found = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] != c && s[i])
			found = 1;
		if (s[i] == c)
		{
			while (s[i] == c && s[i])
				i++;
			if (s[i])
				words++;
		}
		else
			i++;
	}
	return (words + found);
}

static int		w_size(char const *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	int		count;
	int		words;
	char	**array;

	count = -1;
	if (!s)
		return (NULL);
	words = count_words(s, c);
	if (!(array = malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	while (++count < words)
	{
		while (*s == c)
			s++;
		if (!(array[count] = ft_strsub(s, 0, w_size(s, c))))
		{
			while (count > 0)
				free(array[count--]);
			free(array);
			return (NULL);
		}
		s += ft_strlen(array[count]);
	}
	array[count] = 0;
	return (array);
}
