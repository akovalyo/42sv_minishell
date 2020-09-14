/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <akovalyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 11:55:46 by akovalyo          #+#    #+#             */
/*   Updated: 2020/09/14 11:34:18 by akovalyo         ###   ########.fr       */
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

void	void_comm(t_shell *sh, char **tab_comm)
{
	ft_printf("minishell: command not found: %s\n", tab_comm[0]);
}

void		echo_comm(t_shell *sh, char **tab_comm)
{
	if (sh->arg_1 == 0)
		ft_printf("\n");
}

void		check_builtins(t_shell *sh, char **tab_comm)
{
	if (ft_strncmp(tab_comm[0], "exit", 5) == 0)
		sh->exit = 1;
	else if (ft_strncmp(tab_comm[0], "echo", 5) == 0)
		sh->comm = ECHO;

}

void		parse_line(t_shell *sh, char **tab_comm)
{
	check_builtins(sh, tab_comm);
	if (ft_strarraylen(tab_comm) > 1)
	{
		sh->arg_1 = 1;
		if (ft_strncmp(tab_comm[1], "-n", 3) == 0)
			sh->n = 1;
	}
}

void	exec_lines(t_shell *sh)
{
	int		i;
	char	**tab_comm;
	int				ret;
	static void		(*exec_comm[])(t_shell*, char**) = {void_comm, echo_comm};
	
	i = 0;
	while (sh->lines[i])
	{
		tab_comm = ft_strsplit_space(sh->lines[i]);
		i++;
		parse_line(sh, tab_comm);
		if (sh->exit)
			exit_shell(sh, NULL);
		// else if (!sh->comm)
		// 	ft_printf("minishell: command not found: %s\n", tab_comm[0]);
		exec_comm[sh->comm](sh, tab_comm);
		ft_strtab_free(tab_comm, ft_strarraylen(tab_comm));
	}
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
