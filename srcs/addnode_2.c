/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addnode_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:29:00 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/30 11:05:07 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		addnode_spaces(char *str, int i)
{
	int		start;
	t_list	*new;

	start = i;
	new = malloc(sizeof(t_list));
	while (str[i] && ft_isspace(str[i]))
		i++;
	new->content = NULL;
	new->content_size = 0;
	new->ctg = SP;
	new->atr = i - start;
	new->next = NULL;
	ft_lstadd_back(&(g_sh.tokens), new);
	return (i);
}

t_list 	*specialch_create_node(char *str, int i)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (str[i] == '\'')
	{
		new->ctg = SN_QT;
		g_sh.sn_qt += 1;
	}
	else if (str[i] == '"')
	{
		new->ctg = DB_QT;
		g_sh.db_qt += 1;
	}
	else if (str[i] == '<')
		new->ctg = LESS_SIGN;
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			new->ctg = DB_GR_SIGN;
		else
			new->ctg = GR_SIGN;
	}
	else if (str[i] == '|')
		new->ctg = PIPE;
	return (new);
}

int		addnode_specialch(char *str, int i)
{
	t_list	*new;
	
	new = specialch_create_node(str, i);
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
	else if (new->ctg == PIPE)
		new->content = ft_strdup("|");		
	if (new->ctg == GR_SIGN || new->ctg == DB_GR_SIGN)
	{
		g_sh.red_count++;
		new->atr = g_sh.red_count;
	}
	new->content_size = 0;
	new->next = NULL;
	ft_lstadd_back(&(g_sh.tokens), new);
	return (new->ctg == DB_GR_SIGN ? i + 2 : i + 1);
}
