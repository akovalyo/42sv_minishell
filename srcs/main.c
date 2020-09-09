/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:55:46 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/09 13:23:44 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**read_input()
{
	char	*input;
	char	**tab_comms;
	int		tab_len;
	int		i;
	int		ret;

	i = 0;
	if ((ret = get_next_line(0, &input)) < 0)
	{
		ft_printf("minishell: read error");
		free(input);
		return NULL;
	}
	else if (ret == 0)
	{
		free(input);
		ft_printf("\n");
		exit(0);
	}
	tab_comms = ft_strsplit(input, ';');
	free(input);
	return (tab_comms);
}

void	tab_free(char **tab, int len)
{
	while (len > 0)
		free(tab[len--]);
	free(tab);
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
		tab_free(tab_comm, ft_strarraylen(tab_comm));
	}
}

void prompt_msg(void)
{
	char	buff[256];

	ft_printf("%s: ", getcwd(buff, 256));
}

void	clear_scr(void)
{
	ft_printf("\e[1;1H\e[2J");
}

void	sig_func(int sig)
{
	ft_printf("\nnum: %d\nSIGINT: %d\n", sig, SIGINT);
	if (sig == SIGINT)
	{
		ft_printf("\n");
		prompt_msg();
		signal(SIGINT, sig_func);
	}
}

void	sig_sl(int sig)
{
	sig = 0;
	signal(SIGQUIT, sig_sl);
}

int		main(int argc, char **argv)
{
	char	*input;
	char	**comms;

	clear_scr();
	while (1)
	{
		prompt_msg();
		signal(SIGINT, sig_func);
		signal(SIGQUIT, sig_sl);
		comms = read_input();
		run_comms(comms);
		tab_free(comms, ft_strarraylen(comms));
	}
	return (0);
}
