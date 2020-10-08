/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addtoken_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:29:00 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/07 12:52:46 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Creates token 'spaces' and adds to the token list.
*/

int		addtoken_spaces(char *str, int i)
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
** Creates token 'special sign' and adds to the token list.
*/

int		addtoken_specialch(char *str, int i)
{
	t_list	*new;
	
	new = specialch_create_token(str, i);
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
** Creates token 'redirection sign' and adds it to the token list
*/

int		addtoken_redir(char *str, int i)
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
** Converts '$?' to the number showing the return of the previous command,
** creates token 'string' and adds it to the token list.
*/

int		addtoken_status(char *str, int i)
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
