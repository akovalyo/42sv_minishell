/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 10:36:45 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/13 11:23:31 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		hex_ascii(size_t n, int letter)
{
	if (n <= 9)
		return (n + '0');
	else if (letter == 0)
		return (n + 87);
	else
		return (n + 55);
}

char	*conv_base_uns(size_t nbr, int base, char letter)
{
	char	ch;
	char	*str;

	str = NULL;
	if (nbr >= (size_t)base)
		str = conv_base_uns(nbr / base, base, letter);
	ch = hex_ascii(nbr % base, letter);
	return (ft_straddchr_free(str, ch));
}

char	*conv_base(unsigned int nbr, unsigned int base, int letter)
{
	char	ch;
	char	*str;

	str = NULL;
	if (nbr >= base)
		str = conv_base(nbr / base, base, letter);
	ch = hex_ascii(nbr % base, letter);
	return (ft_straddchr_free(str, ch));
}

char	*strdup_printf(const char *s)
{
	char *d;

	if (!s)
		return (ft_strdup("(null)"));
	if (!(d = (char *)malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (NULL);
	ft_strcpy(d, s);
	return (d);
}
