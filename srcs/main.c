/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:55:46 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/04 12:48:40 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input()
{
	char	*input;
	int		ret;
	char	buf;

	read(0, &buf, 1);
	// while ((ret = read(0, &buf, 1)) && buf != '\n')
	// {

	// }
	ft_printf("OK\n");
}

int		main(int argc, char **argv)
{
	char	*cwd;
	char	*input;
	char	buff[256];

	cwd = getcwd(buff, 256);
	ft_printf("%s: ", cwd);
	// input = read_input();
	read_input();
	return (0);
}
