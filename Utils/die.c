/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:48:48 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/17 14:37:46 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_shell_errno;

int	ft_free_env(t_env **env)
{
	ft_free((void **)&(*env)->name);
	ft_free((void **)&(*env)->value);
	ft_free((void **)env);
	return (0);
}

/*
DESCRIPTION
this function does the free of a list and it's content
in this case the content is another list with some variables
inside it
*/
void	ft_free_list(t_list **list)
{
	t_list	*tmp_list;
	t_env	*tmp_env;

	tmp_list = 0;
	while (*list)
	{
		tmp_env = 0;
		tmp_list = (*list)->next;
		while ((*list)->content)
		{
			tmp_env = (*list)->content->next;
			ft_free_env(&((*list)->content));
			(*list)->content = tmp_env;
		}
		ft_free((void **)&(*list));
		(*list) = tmp_list;
	}
}

void	ft_free_routine(t_shell *shell)
{
	ft_free((void **)&(shell->line));
	if (shell->parsed)
		ft_free_mat((void ***)&shell->parsed);
	if (shell->red.infiles)
		ft_free_mat((void ***)&(shell->red.infiles));
	if (shell->red.outfiles)
		ft_free_mat((void ***)&(shell->red.outfiles));
	if (shell->red.afiles)
		ft_free_mat((void ***)&(shell->red.afiles));
	if (shell->red.fdin)
		ft_free((void **)&(shell->red.fdin));
	if (shell->red.fdout)
		ft_free((void **)&(shell->red.fdout));
	if (shell->red.fda)
		ft_free((void **)&(shell->red.fda));
	if (shell->lvls)
		ft_free((void **)&(shell->lvls));
	if (shell->files)
		ft_free_mat((void ***)&(shell->files));
	ft_free_exp(&shell->exp);
	ft_free_mat((void ***)&(shell->envp));
	shell->envp = list_convert(shell->list, 0);
	if (!shell->envp)
		ft_die(shell, 1, 12);
}

/*
DESCRIPTION
this function does the free of all the variables in the struct [shell]
also the structs inside the [shell] like [pipex] and so on
*/
void	ft_free_shell(t_shell *shell)
{
	if (shell->fd_input)
		ft_free((void **)&(shell->fd_input));
	if (shell->fd_output)
		ft_free((void **)&(shell->fd_output));
	if (shell->pipex.pipe)
		ft_free((void **)&(shell->pipex.pipe));
	if (shell->pipex.pid)
		ft_free((void **)&(shell->pipex.pid));
	if (shell->envp)
		ft_free_mat((void ***)&(shell->envp));
}

/*
DESCRIPTION
this function does the free of all the variables in t_shell and *in base a
todo esce dal programma o ritorna un numero*
*/
int	ft_die(t_shell *shell, int todo, int code)
{
	ft_free_routine(shell);
	ft_free_shell(shell);
	g_shell_errno = code;
	if (todo == 1)
	{
		if (shell->list)
			ft_free_list(&shell->list);
		rl_clear_history();
		exit(code);
	}
	else
		return (code);
}
