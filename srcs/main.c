/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:55:46 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/10 17:25:29 by alex             ###   ########.fr       */
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

void	run_comms(t_shell *sh)
{
	int		i;
	
	i = 0;
	while (sh->comms[i])
	{
		sh->tab_comm = ft_strsplit_space(sh->comms[i]);
		i++;
		ft_printf("%d\n", ft_strarraylen(sh->tab_comm));
		ft_strtab_free(sh->tab_comm, ft_strarraylen(sh->tab_comm));
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
	t_shell		sh;

	clear_scr();
	//init_shell(&sh);
	while (1)
	{
		prompt_msg();
		signal(SIGINT, sig_func);
		signal(SIGQUIT, sig_sl);
		sh.comms = read_input();
		run_comms(&sh);
		ft_strtab_free(sh.comms, ft_strarraylen(sh.comms));
	}
	return (0);
}
