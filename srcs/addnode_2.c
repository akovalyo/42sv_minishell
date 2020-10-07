/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addnode_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:29:00 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/07 12:52:46 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/

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

/*
**
*/

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
	else if (str[i] == '|')
		new->ctg = PIPE;
	return (new);
}

/*
**
*/

int		addnode_specialch(char *str, int i)
{
	t_list	*new;
	
	new = specialch_create_node(str, i);
	if (new->ctg == SN_QT)
		new->content = ft_strdup("'");
	else if (new->ctg == DB_QT)
		new->content = ft_strdup("\"");
	else if (new->ctg == PIPE)
		new->content = ft_strdup("|");		
	new->content_size = 0;
	new->next = NULL;
	ft_lstadd_back(&(g_sh.tokens), new);
	return (new->ctg == DB_GR_SIGN ? i + 2 : i + 1);
}

/*
**
*/

int		handle_redir_sign(char *str, int *i)
{
	t_ctg ctg;

	if (str[*i] == '<')
	{
		ctg = LESS_SIGN;
		(*i)++;
	}
	else if (str[*i] == '>')
	{
		(*i)++;
		if (str[*i] == '>')
		{
			ctg = DB_GR_SIGN;
			(*i)++;
		}
		else
			ctg = GR_SIGN;
	}
	return (ctg);
}

/*
**
*/

int		addnode_redir(char *str, int i)
{
	t_list	*new;
	int		start;

	new = malloc(sizeof(t_list));
	new->content = NULL;
	new->ctg = handle_redir_sign(str, &i);
	i = skip_spaces(str, i);
	if (str[i] == '\0')
		print_error("syntax error near unexpected token 'newline'", 1);
	while (str[i] && !ft_isspace(str[i]))
	{	
		if (str[i] == '\\')
			i++;
		new->content = ft_straddchr_free(new->content, str[i]);
		i++;
	}
	new->next = NULL;
	new->comm = VOID;
	ft_lstadd_back(&(g_sh.tokens), new);
	add_to_map(new);
	return (i);
}

/*
**
*/

int		addnode_status(char *str, int i)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->atr = 0;
	new->next = NULL;
	new->content = ft_itoa(g_sh.status[1]);
	new->ctg = STR;
	new->comm = VOID;
	ft_lstadd_back(&(g_sh.tokens), new);
	return (i + 2);
}
