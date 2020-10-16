/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:42:51 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/16 15:17:11 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Tries to change the current directory to the pathname pointed
** to by the 'path'. If failed, prints error.
*/

int		sh_chdir(char *path)
{
	if (chdir(path))
	{
		print_error(strerror(errno), errno);
		return (1);
	}
	return (0);
}

/*
** Updates 'PWD' and 'OLDPWD' variables.
*/

void	update_pwd_envv(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	change_envv("OLDPWD", get_envv("PWD"), NULL);
	change_envv("PWD", pwd, NULL);
}
