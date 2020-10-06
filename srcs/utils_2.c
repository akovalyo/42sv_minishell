/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:42:51 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/06 08:37:03 by akovalyo         ###   ########.fr       */
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

int is_redirect_ctg(t_list *lst)
{
	if (lst->ctg == GR_SIGN || lst->ctg == DB_GR_SIGN || lst->ctg == LESS_SIGN)
		return (1);
	return (0);
}
