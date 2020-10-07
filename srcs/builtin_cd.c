/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:17:53 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/07 12:51:55 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/

void 	cd_home(void)
{
	char *home;

	if (!(home = get_envv("HOME")))
		return ;
	if (sh_chdir(home))
		return ;
	update_pwd_envv();
}

/*
**
*/

char 	*cd_up_2(char **pwd_split, int len)
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
**
*/

void 	cd_up()
{
	char 	*pwd;
	char 	**pwd_split;
	char 	*new_path;
	int		len;
	int		i;

	i = -1;
	pwd = getcwd(NULL, 0);
	pwd_split = ft_strsplit(pwd, '/');
	len = ft_arraylen((void **)pwd_split);
	if (!len)
		return ;
	if (len == 1)
		chdir("/");
	else
	{
		new_path = cd_up_2(pwd_split, len);
		sh_chdir(new_path);
		free(new_path);
	}
	ft_strarr_free(pwd_split);
}

/*
**
*/

void 	cd(char *path)
{
	char *new_path;

	if (ft_strncmp(path, "..", 3) == 0)
		cd_up();
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
**
*/

void	comm_cd(char **argv, int map_i)
{
	int i;
	int argc;
	char **args;

	i = 0;
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
