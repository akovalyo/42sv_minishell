/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addnode_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:29:00 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/25 16:33:53 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list 	*specialch_create_node(char *arg, int i)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (arg[i] == '\'')
	{
		new->ctg = SN_QT;
		g_sh.sn_qt += 1;
	}
	else if (arg[i] == '"')
	{
		new->ctg = DB_QT;
		g_sh.db_qt += 1;
	}
	else if (arg[i] == '<')
		new->ctg = LESS_SIGN;
	else if (arg[i] == '>')
	{
		if (arg[i + 1] == '>')
			new->ctg = DB_GR_SIGN;
		else
			new->ctg = GR_SIGN;
	}
	return (new);
}

int		addnode_specialch(char *arg, int i)
{
	t_list	*new;
	
	new = specialch_create_node(arg, i);
	if (new->ctg == SN_QT)
		new->content = ft_strdup("'");
	else if (new->ctg == DB_QT)
		new->content = ft_strdup("\"");
	else if (new->ctg == LESS_SIGN)
		new->content = ft_strdup("<");
	else if (new->ctg == GR_SIGN)
		new->content = ft_strdup(">");
	else if (new->ctg == DB_GR_SIGN)
		new->content = ft_strdup(">>");	
	new->content_size = 0;
	new->next = NULL;
	new->atr = 0;
	ft_lstadd_back(&(g_sh.pars), new);
	return (new->ctg == 11 ? i + 2 : i + 1);
}
