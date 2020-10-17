/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_bin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:29:13 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/17 16:56:06 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_path(char *str)
{
	struct stat		sb;
	char			*tmp;
	char			*tmp_path;

	tmp = NULL;
	if (ft_strlen(str) > 1 && ft_strncmp(str, "./", 2) == 0)
		tmp = str;
	else if (ft_strlen(str) > 2 && ft_strncmp(str, "../", 2) == 0)
		tmp = str;
	else if (ft_strncmp(str, "/", 1) == 0)
		tmp = str;
	if (tmp && stat(str, &sb) == 0 && !S_ISDIR(sb.st_mode))
		return (1);
	tmp_path = ft_strdup(get_envv("PWD"));
	if (ft_strncmp(tmp_path, "/", 2))
		tmp_path = ft_straddchr_free(tmp_path, '/');
	tmp_path = ft_strjoin_free(tmp_path, str);
	if (stat(tmp_path, &sb) == 0 && !S_ISDIR(sb.st_mode))
	{
		free(tmp_path);
		return (1);
	}
	free(tmp_path);
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
