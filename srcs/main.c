/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:55:46 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/11 18:39:51 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_shell *sh, char *message)
{
	if (message)
		ft_printf("minishell: %s", message);
	if (sh->input)
		free(sh->input);
	if (sh->lines)
		ft_strtab_free(sh->lines, ft_strarraylen(sh->lines));
	//ft_printf("\n");
	exit(0);
}

char	**read_input(t_shell *sh)
{
	char	**tab_lines;
	int		tab_len;
	int		i;
	int		ret;

	i = 0;
	if ((ret = get_next_line(0, &(sh->input))) < 0)
		exit_shell(sh, "read error");
	else if (ret == 0)
		exit_shell(sh, NULL);
	tab_lines = ft_strsplit(sh->input, ';');
	free(sh->input);
	sh->input = NULL;
	return (tab_lines);
}

int		check_builtins(t_shell *sh, char *comm)
{
	if (ft_strcmp(comm, "exit") == 0)
		return (-1);
	return (0);
}

int		parse_line(t_shell *sh, char **tab_comm)
{
	int		builtin;
	
	if ((builtin = check_builtins(sh, tab_comm[0])) == -1)
		 return (-1);
	return (0);
}

void	exec_lines(t_shell *sh)
{
	int		i;
	char	**tab_comm;
	int		ret;
	
	i = 0;
	while (sh->lines[i])
	{
		tab_comm = ft_strsplit_space(sh->lines[i]);
		i++;
		ret = parse_line(sh, tab_comm);
		// ft_printf("%d\n", ft_strarraylen(sh->tab_comm));
		ft_strtab_free(tab_comm, ft_strarraylen(tab_comm));
		if (ret == -1)
			exit_shell(sh, NULL);
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

void	init_shell(t_shell *sh)
{
	sh->lines = NULL;
	sh->input = NULL;
}

int		main(int argc, char **argv, char **env)
{
	t_shell		sh;

	clear_scr();
	init_shell(&sh);

	int i = 1;
	// while (env[i])
	// {
	// 	ft_printf("%s\n", env[i]);
	// 	i++;
	// }
	while (1)
	{
		prompt_msg();
		signal(SIGINT, sig_func);
		signal(SIGQUIT, sig_sl);
		sh.lines = read_input(&sh);
		exec_lines(&sh);
		ft_strtab_free(sh.lines, ft_strarraylen(sh.lines));
		sh.lines = NULL;
	}
	return (0);
}
