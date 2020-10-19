/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_bin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:29:13 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/19 12:00:01 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_tilde(t_list **node)
{
	char	*ptr1;
	char	*ptr2;

	ptr1 = ft_strdup(get_envv("HOME"));
	ptr2 = (*node)->content;
	(*node)->content = ft_strjoin(ptr1, ptr2 + 1);
	free(ptr1);
	free(ptr2);
	return ("");
}

int		check_path(t_list **node)
{
	struct stat		sb;
	char			*tmp;

	tmp = NULL;
	if (ft_strlen((*node)->content) > 1 &&
		ft_strncmp((*node)->content, "./", 2) == 0)
		tmp = (*node)->content;
	else if (ft_strlen((*node)->content) > 2 &&
		ft_strncmp((*node)->content, "../", 3) == 0)
		tmp = (*node)->content;
	else if (ft_strncmp((*node)->content, "/", 2) == 0)
		print_error("/: is a directory", 126);
	else if (ft_strncmp((*node)->content, "/", 1) == 0)
		tmp = (*node)->content;
	else if (ft_strncmp((*node)->content, "~", 1) == 0)
		tmp = replace_tilde(node);
	if (tmp && stat((*node)->content, &sb) == 0 && !S_ISDIR(sb.st_mode))
		return (1);
	return (0);
}

int		check_relative_path(t_list **node)
{
	char			*path;
	struct stat		sb;

	path = ft_strdup(get_envv("PWD"));
	if (ft_strncmp(path, "/", 2))
		path = ft_straddchr_free(path, '/');
	path = ft_strjoin_free(path, (*node)->content);
	if (stat(path, &sb) == 0 && !S_ISDIR(sb.st_mode))
		return (replace_content(node, path, NULL));
	free(path);
	return (0);
}
