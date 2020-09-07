/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:01:24 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/07 12:08:56 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char const *s)
{
	int i;
	int words;
	int found;

	i = 0;
	words = 0;
	found = 0;
	while (ft_isspace(s[i]) && s[i])
		i++;
	while (s[i])
	{
		if (ft_isspace(s[i]) == 0 && s[i])
			found = 1;
		if (ft_isspace(s[i]))
		{
			while (ft_isspace(s[i]) && s[i])
				i++;
			if (s[i])
				words++;
		}
		else
			i++;
	}
	return (words + found);
}

static int		w_size(char const *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isspace(str[i]) == 0)
		i++;
	return (i);
}

char			**ft_strsplit_space(char const *s)
{
	int		count;
	int		words;
	char	**array;

	count = -1;
	if (!s)
		return (NULL);
	words = count_words(s);
	if (!(array = malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	while (++count < words)
	{
		while (ft_isspace(*s))
			s++;
		if (!(array[count] = ft_strsub(s, 0, w_size(s))))
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
