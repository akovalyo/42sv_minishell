/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:42:51 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/30 18:10:16 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 		special_char(char c)
{
	if (c == '\'' || c == '"' || c == '$')
		return (1);
	return (0);
}

int 		isredir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int 		isquote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}
