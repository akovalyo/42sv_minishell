/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:17:53 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/09 17:55:45 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Changes the current directory to the HOME directory
*/

void	cd_home(void)
{
	char *home;

	if (!(home = get_envv("HOME")))
		return ;
	if (sh_chdir(home))
		return ;
	update_pwd_envv();
}

/*
** Helper cd_above function, creates the new path to the directory one level
** above the current.
*/

char	*cd_above_2(char **pwd_split, int len)
{
	char	*new_path;
	int		i;

	i = -1;
	new_path = ft_strdup("/");
	while (++i < len - 1)
	{
		new_path = ft_strjoin_free(new_path, pwd_split[i]);
		new_path = ft_straddchr_free(new_path, '/');
	}
	return (new_path);
}

/*
** Changes the current directory to the directory above.
*/

void	cd_above(void)
{
	char	*pwd;
	char	**pwd_split;
	char	*new_path;
	int		len;

	pwd = getcwd(NULL, 0);
	pwd_split = ft_strsplit(pwd, '/');
	free(pwd);
	len = ft_arraylen((void **)pwd_split);
	if (!len)
		return ;
	if (len == 1)
		chdir("/");
	else
	{
		new_path = cd_above_2(pwd_split, len);
		sh_chdir(new_path);
		free(new_path);
	}
	ft_strarr_free(pwd_split);
}

/*
** Root command for changing the current directory. Function updates
** the environment variable.
*/

void	cd(char *path)
{
	char	*new_path;

	if (ft_strncmp(path, "..", 3) == 0)
		cd_above();
	else if (ft_strncmp(path, "-", 2) == 0)
		sh_chdir(get_envv("OLDPWD"));
	else if (path[0] == '/')
	{
		if (sh_chdir(path))
			return ;
	}
	else
	{
		new_path = ft_strdup(get_envv("PWD"));
		new_path = ft_straddchr_free(new_path, '/');
		new_path = ft_strjoin_free(new_path, path);
		sh_chdir(new_path);
		free(new_path);
	}
	update_pwd_envv();
}

/*
** Executes the builtin cd command
*/

void	comm_cd(char **argv)
{
	int		argc;
	char	**args;

	argc = ft_arraylen((void **)argv);
	if (argc == 1)
		cd_home();
	else if (argc == 2)
	{
		args = ft_strsplit(argv[1], ' ');
		if (ft_arraylen((void **)args) > 1)
		{
			g_sh.error++;
			g_sh.status[0] = 1;
			ft_printf("minishell: string not in pwd: %s\n", argv[1]);
			return ;
		}
		else
			cd(args[0]);
		ft_strarr_free(args);
	}
}
