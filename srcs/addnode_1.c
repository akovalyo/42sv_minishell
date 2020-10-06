/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addnode_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:27:01 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/06 11:45:15 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		addnode_comm(char *str, int i)
{
	t_list	*new;
	int start;

	new = malloc(sizeof(t_list));
	if (str[i] == '|')
	{
		i++;
		new->ctg = PIPE;
	}
	i = skip_spaces(str, i++);
	start = i;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	new->content = ft_strsub(str, start, i - start);
	new->comm = (i == start) ? VOID : check_builtins_and_bin(new->content);
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


int		addnode_flags(char *str, int i)
{
	int 	start;
	t_list	*new;
	
	start = i;
	if (ft_isalpha(str[i + 1]))
	{
		i++;
		while (str[i] && ft_isalpha(str[i]))
			i++;
		new = malloc(sizeof(t_list));
		//g_sh.flags++;
		new->content = ft_strsub(str, start, i - start);
		new->content_size = i - start;
		new->ctg = FLAG;
		new->comm = VOID;
		new->atr = 0;
		new->next = NULL;
		ft_lstadd_back(&(g_sh.tokens), new);
		return (i);
	}
	g_sh.fl_ignore = 1;
	return (start);
}



int		addnode_envv(char *str, int i)
{
	int 	start;
	t_list	*new;
	char 	*tmp;
	char	*ptr_env;
	
	start = i;
	i++;
	while (str[i] && ft_isalpha(str[i]))
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

int		addnode_tilde(char *str, int i)
{
	int 	start;
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
	new->content_size = ft_strlen(new->content);
	new->atr = 0;
	new->next = NULL;
	new->ctg = STR;
	new->comm = VOID;
	ft_lstadd_back(&(g_sh.tokens), new);
	return (i);
}

int		addnode_str(char *str, int i)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->content = NULL;
	new->comm = VOID;
	while (str[i] && !special_char(str[i]) && !isredir(str[i]) && str[i] != '$' && !ft_isspace(str[i]) && str[i] != '|')
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
