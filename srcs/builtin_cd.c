/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:17:53 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/03 15:20:14 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void cd_home(void)
{
	char *home;
	
	if (!(home = ft_strdup(get_env("HOME"))))
	{
		print_error("failed to load env variable", 1);
		return ;
	}
	if (chdir(home))
	{
		free(home);
		print_error(strerror(errno), errno);
		return ;
	}
	free(home);
	update_pwd();
	ft_printf("%s\n", g_sh.pwd);
}

void		comm_cd(char **arg, int map_i)
{
	int i;

	i = 0;

	
	if (ft_arraylen((void **)arg) == 1)
		cd_home();
	// if ()
	// while (arg[i])
	// {
	// 	ft_printf("%s\n", arg[i]);
	// 	i++;
	// }
	// return ;
}