/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:55:46 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/07 12:21:10 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**read_input()
{
	char	*input;
	char	**tab_comms;
	int		tab_len;
	int		i;

	i = 0;
	if (get_next_line(0, &input) < 0)
	{
		ft_printf("minishell: read error");
		free(input);
		return NULL;
	}
	tab_comms = ft_strsplit(input, ';');
	free(input);
	// tab_len = ft_strarraylen(tab);
	// while (i < tab_len)
	// {
	// 	ft_printf("%s\n", tab[i]);
	// 	i++;
	// }
	// ft_printf("%d\n", tab_len);
	return (tab_comms);
}

void	run_comms(char **comms)
{
	int		i;
	char	**tab_comm;
	
	i = 0;
	while (comms[i])
	{
		tab_comm = ft_strsplit_space(comms[i]);
		i++;
		ft_printf("%d\n", ft_strarraylen(tab_comm));
	}
}

int		main(int argc, char **argv)
{
	char	*cwd;
	char	*input;
	char	buff[256];
	char	**comms;

	cwd = getcwd(buff, 256);
	ft_printf("%s: ", cwd);
	// input = read_input();
	comms = read_input();
	run_comms(comms);
	return (0);
}
