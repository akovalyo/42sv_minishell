/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addnode_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:27:01 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/25 16:36:09 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		addnode_flags(char *arg, int i)
{
	int 	start;
	t_list	*new;
	
	start = i;
	if (ft_isalpha(arg[i + 1]))
	{
		i++;
		while (arg[i] && ft_isalpha(arg[i]))
			i++;
		new = malloc(sizeof(t_list));
		g_sh.flags++;
		new->content = ft_strsub(arg, start, i - start);
		new->content_size = i - start;
		new->ctg = FLAG;
		new->atr = 0;
		new->next = NULL;
		ft_lstadd_back(&(g_sh.pars), new);
		return (i);
	}
	g_sh.fl_ignore = 1;
	return (start);
}

int		addnode_envv(char *arg, int i)
{
	int 	start;
	t_list	*new;
	char 	*tmp;
	char	*ptr_env;
	
	start = i;
	i++;
	while (arg[i] && ft_isalpha(arg[i]))
		i++;
	new = malloc(sizeof(t_list));
	tmp = ft_strsub(arg, start, i - start);
	new->atr = 0;
	new->next = NULL;
	if ((ptr_env = get_env(tmp + 1)))
		new->content = ft_strdup(ptr_env);
	else
		new->content = ft_strdup(tmp);
	new->content_size = ft_strlen(new->content);
	new->ctg = STR;
	ft_lstadd_back(&(g_sh.pars), new);
	free(tmp);
	return (i);
}

int		addnode_tilde(char *arg, int i)
{
	int 	start;
	t_list	*new;
	char	*rest;
	char	*ptr;

	
	start = i + 1;
	i++;
	while (arg[i] && !special_char(arg[i]) && !ft_isspace(arg[i]))
		i++;
	new = malloc(sizeof(t_list));
	ptr = get_env("HOME");
	new->content = ft_strdup(ptr);
	if (start != i)
	{
		rest = ft_strsub(arg, start, i - start);
		ptr = new->content;
		new->content = ft_strjoin(new->content, rest);
		free(ptr);
		free(rest);
	}
	new->content_size = ft_strlen(new->content);
	new->atr = 0;
	new->next = NULL;
	new->ctg = STR;
	ft_lstadd_back(&(g_sh.pars), new);
	return (i);
}

int		addnode_str(char *arg, int i)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->content = NULL;
	while (arg[i] && !special_char(arg[i]) && arg[i] != '$' && !ft_isspace(arg[i]))
	{	
		if (arg[i] == '\\')
			i++;
		new->content = ft_straddchr_free(new->content, arg[i]);
		i++;
	}
	new->content_size = ft_strlen(new->content);
	new->atr = 0;
	new->next = NULL;
	new->ctg = STR;
	ft_lstadd_back(&(g_sh.pars), new);
	return (i);
}

int		addnode_spaces(char *arg, int i)
{
	int		start;
	t_list	*new;

	start = i;
	new = malloc(sizeof(t_list));
	while (arg[i] && ft_isspace(arg[i]))
		i++;
	new->content = NULL;
	new->content_size = 0;
	new->ctg = SP;
	new->atr = i - start;
	new->next = NULL;
	ft_lstadd_back(&(g_sh.pars), new);
	return (i);
}
