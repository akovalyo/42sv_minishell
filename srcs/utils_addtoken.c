/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_addtoken.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 23:23:02 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/07 23:50:59 by akovalyo         ###   ########.fr       */
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
	return (ctg);
}

/*
** Sets the category of the token 'special sign'.
*/

t_list 	*specialch_create_token(char *str, int i)
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