/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addtoken_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 14:57:54 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/17 11:37:28 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Creates token 'command' and adds it to the token list
*/

int		addtoken_comm(char *str, int i)
{
	t_list	*new;
	int		start;

	new = malloc(sizeof(t_list));
	if (str[i] == '|')
	{
		i++;
		new->ctg = PIPE;
	}
	i = skip_spaces(str, i++);
	start = i;
	while (str[i] && !ft_isspace(str[i]) && !isredir(str[i]) && str[i] != '|')
		i++;
	new->content = ft_strsub(str, start, i - start);
	new->comm = (i == start) ? VOID : check_builtins_and_bin(&new);
	new->next = NULL;
	if (new->comm != VOID && new->comm != NOCOMM && new->ctg != PIPE)
	{
		new->ctg = COMM;
		g_sh.n_comm++;
		new->atr = g_sh.n_comm;
	}
	add_to_map(new);
	ft_lstadd_back(&(g_sh.tokens), new);
	return (i);
}

/*
** Creates token 'flag' and adds to the token list
*/

int		addtoken_flags(char *str, int i)
{
	int		start;
	t_list	*new;

	start = i;
	if (ft_isalpha(str[i + 1]))
	{
		i++;
		while (str[i] && ft_isalpha(str[i]))
			i++;
		new = malloc(sizeof(t_list));
		new->content = ft_strsub(str, start, i - start);
		new->content_size = i - start;
		new->ctg = FLAG;
		new->comm = VOID;
		new->atr = 0;
		new->next = NULL;
		ft_lstadd_back(&(g_sh.tokens), new);
		return (i);
	}
	return (start);
}

/*
** Creates token 'environment variable' and adds it to the token list
*/

int		addtoken_envv(char *str, int i)
{
	int		start;
	t_list	*new;
	char	*tmp;
	char	*ptr_env;

	start = i;
	i++;
	while (str[i] && ft_isprint(str[i]) && !ft_isspace(str[i])
			&& !ft_strchr(RESERVED, str[i]))
		i++;
	new = malloc(sizeof(t_list));
	tmp = ft_strsub(str, start, i - start);
	new->atr = 0;
	new->next = NULL;
	if ((ptr_env = get_envv(tmp + 1)))
		new->content = ft_strdup(ptr_env);
	else
		new->content = ft_strdup(tmp);
	new->content_size = ft_strlen(new->content);
	new->ctg = STR;
	new->comm = VOID;
	ft_lstadd_back(&(g_sh.tokens), new);
	free(tmp);
	return (i);
}

/*
** Creates token 'tilde' and adds it to the token list
*/

int		addtoken_tilde(char *str, int i)
{
	int		start;
	t_list	*new;
	char	*rest;
	char	*ptr;

	start = i + 1;
	i++;
	while (str[i] && !special_char(str[i]) && !ft_isspace(str[i]))
		i++;
	new = malloc(sizeof(t_list));
	ptr = get_envv("HOME");
	new->content = ft_strdup(ptr);
	if (start != i)
	{
		rest = ft_strsub(str, start, i - start);
		ptr = new->content;
		new->content = ft_strjoin(new->content, rest);
		free(ptr);
		free(rest);
	}
	token_tilde_init(&new);
	ft_lstadd_back(&(g_sh.tokens), new);
	return (i);
}

/*
** Creates token 'string' and adds it to the token list
*/

int		addtoken_str(char *str, int i)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->content = NULL;
	new->comm = VOID;
	while (str[i] && !special_char(str[i]) && !isredir(str[i]) &&
			str[i] != '$' && !ft_isspace(str[i]) && str[i] != '|')
	{
		if (str[i] == '\\')
			i++;
		new->content = ft_straddchr_free(new->content, str[i]);
		i++;
	}
	new->content_size = ft_strlen(new->content);
	new->atr = 0;
	new->next = NULL;
	new->ctg = STR;
	ft_lstadd_back(&(g_sh.tokens), new);
	return (i);
}
