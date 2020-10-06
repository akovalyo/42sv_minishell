/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:17:53 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/05 18:52:12 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void update_pwd_envv(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	change_envv("OLDPWD", get_envv("PWD"));
	change_envv("PWD", pwd);

	free(pwd);

		
	// ft_printf("%s\n", pwd);
}

void cd_home(void)
{
	char *home;

	
	if (!(home = get_envv("HOME")))
		return ;
	if (chdir(home))
	{
		print_error(strerror(errno), errno);
		return ;
	}
	update_pwd_envv();


}

void cd_one(char *path)
{


}

void		comm_cd(char **arg, int map_i)
{
	int i;
	int len;
	char **args;

	i = 0;
	len = ft_arraylen((void **)arg);
	
	if (len == 1)
		cd_home();
	else if (len == 2)
	{
		args = ft_strsplit(arg[1], ' ');
		if (ft_arraylen((void **)args) > 1)
		{
			g_sh.error = 1;
			g_sh.status[0] = 1;
			ft_printf("minishell: string not in pwd: %s\n", arg[1]);
			return ;
		}
		else
			cd_one(args[0]);
		ft_strarr_free(args);
	}
}