/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 14:09:01 by akovalyo          #+#    #+#             */
/*   Updated: 2020/10/14 12:55:41 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Adds command to the command array for execution
*/

char	**add_to_argv_comm(t_list **lstptr)
{
	char **arr;

	arr = malloc(sizeof(char *) * 2);
	arr[0] = ft_strdup((*lstptr)->content);
	arr[1] = NULL;
	*lstptr = (*lstptr)->next;
	return (arr);
}

/*
** Adds flags to the command array
*/

char	**add_to_arg_flag(char **arr, t_list **lstptr)
{
	arr = add_elem_to_arr(arr, (*lstptr)->content, NULL);
	*lstptr = (*lstptr)->next;
	return (arr);
}

/*
** Adds string to the command array
*/

char	**add_elem_to_arr(char **arr, char *str, void (*del)(void *))
{
	char	**new;
	int		i;
	int		size;

	i = 0;
	size = ft_arraylen((void **)arr);
	new = malloc(sizeof(char *) * (size + 2));
	while (i < size)
	{
		new[i] = ft_strdup(arr[i]);
		free(arr[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	if (del)
		del(str);
	i++;
	new[i] = NULL;
	free(arr);
	return (new);
}

/*
** Adds rest tokens to the command array
*/

char	**add_to_argv_else(char **arr, t_list **lstptr)
{
	char *str;

	str = NULL;
	while ((*lstptr) && (*lstptr)->ctg != PIPE && is_redirect_ctg(*lstptr) != 1)
	{
		if ((*lstptr)->ctg == DB_QT || (*lstptr)->ctg == SN_QT)
			arr = add_elem_to_arr(arr, between_quotes(str, lstptr), free);
		else if ((*lstptr)->ctg == STR)
			arr = add_elem_to_arr(arr, (*lstptr)->content, NULL);
		*lstptr = (*lstptr == NULL) ? NULL : (*lstptr)->next;
	}
	g_sh.flag = 0;
	return (arr);
}

/*
** Creates the command array.
*/

char	**create_argv(t_list *lstptr)
{
	char	**arr;

	arr = add_to_argv_comm(&lstptr);
	while (lstptr && lstptr->ctg != PIPE && is_redirect_ctg(lstptr) != 1)
	{
		if (lstptr->ctg == SP)
			lstptr = lstptr->next;
		if (lstptr == NULL)
			break ;
		if (lstptr->ctg == FLAG && g_sh.flag)
			arr = add_to_arg_flag(arr, &lstptr);
		else
			arr = add_to_argv_else(arr, &lstptr);
	}
	return (arr);
}
