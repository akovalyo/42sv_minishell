/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins_and_bin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:38:07 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/08 15:07:16 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Helper function to replace content in the structure
*/

int		replace_content(t_list **node, char *cont, char **paths)
{
	char *tmp;

	tmp = (*node)->content;
	(*node)->content = ft_strdup(cont);
	free(tmp);
	free(cont);
	ft_strarr_free(paths);
	return (1);
}

/*
** Creates path to check if the binary file exists
*/

char	*create_path(char *bin, char *comm)
{
	char *path;

	path = NULL;
	path = ft_strdup(bin);
	path = ft_straddchr_free(path, '/');
	path = ft_strjoin_free(path, comm);
	return (path);
}

/*
** Checks existing system executable for the first argument
*/

int		check_bin(t_list **node)
{
	char			**paths;
	int				i;
	struct stat		sb;
	char			*tmp_path;

	if (ft_strncmp((*node)->content, "/", 1) == 0)
	{
		if (stat((*node)->content, &sb) == 0 && !S_ISDIR(sb.st_mode))
			return (1);
		return (0);
	}
	i = -1;
	if (!(paths = ft_strsplit(get_envv("PATH"), ':')))
		return (0);
	while (paths[++i])
	{
		tmp_path = create_path(paths[i], (*node)->content);
		if (stat(tmp_path, &sb) == 0)
			return (replace_content(node, tmp_path, paths));
		free(tmp_path);
	}
	ft_strarr_free(paths);
	return (0);
}

/*
** Checks builtin commands and existing system executable for the argument
*/

t_comm	check_builtins_and_bin(t_list **new)
{
	if (ft_strnequ_alpha((*new)->content, "exit", 5) == 0)
		g_sh.exit = 1;
	else if (ft_strnequ_alpha((*new)->content, "echo", 5) == 0)
		return (ECHO);
	else if (ft_strnequ_alpha((*new)->content, "pwd", 4) == 0)
		return (PWD);
	else if (ft_strnequ_alpha((*new)->content, "cd", 3) == 0)
		return (CD);
	else if (ft_strnequ_alpha((*new)->content, "export", 7) == 0)
		return (EXPORT);
	else if (ft_strnequ_alpha((*new)->content, "unset", 6) == 0)
		return (UNSET);
	else if (ft_strnequ_alpha((*new)->content, "env", 4) == 0)
		return (ENV);
	else if (check_bin(new))
		return (SH);
	else
		return (NOCOMM);
	return (VOID);
}
