/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_addtoken.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 23:23:02 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/16 17:53:25 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Sets the category of the token 'redirection sign'.
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
	else
		ctg = 0;
	return (ctg);
}

/*
** Sets the category of the token 'special sign'.
*/

t_list	*specialch_create_token(char *str, int i)
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
** Sets atributes of the token 'tilde'.
*/

void	token_tilde_init(t_list **token)
{
	(*token)->atr = 0;
	(*token)->next = NULL;
	(*token)->ctg = STR;
	(*token)->comm = VOID;
}

/*
** Checks if token is between quotes.
*/

int		isbetween_quotes(void)
{
	if (g_sh.sn_qt % 2 == 0 && g_sh.db_qt % 2 == 0)
		return (0);
	return (1);
}

/*
** Checks tokens, if it's allowed to add flags to it, returns 1.
*/

int		flags_allowed(void)
{
	t_list *head;

	head = g_sh.tokens;
	while (head && head->ctg == SP && head->ctg == COMM)
	{
		head = head->next;
	}
	if (head == NULL)
		return (1);
	return (0);
}
