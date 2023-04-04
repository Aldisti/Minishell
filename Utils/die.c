
#include "../minishell.h"

/*
DESCRIPTION
this function does the free of a list and it's content
in this case the content is another list with some variables
inside it
UPGRADES
(si potrebbe richiedere come argomento della funzione il puntatore
ad una funzione che faccia il free del content, così da rendere questa
funzione utilizzabile anche con altre liste, mi sa che abbiamo già fatto
una cosa del genere in Libft)
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
			ft_free((void **)&((*list)->content->name));
			ft_free((void **)&((*list)->content->value));
			ft_free((void **)&(*list)->content);
			(*list)->content = tmp_env;
		}
		ft_free((void **)&(*list));
		(*list) = tmp_list;
	}
}

void ft_free_red(t_shell *shell)
{
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
}

/*
DESCRIPTION
this function does the free of all the variables in the struct [shell]
also the structs inside the [shell] like [pipex] and so on
UPGRADES
(si potrebbe aggiungere un parametro [n] ed in base a quello fare i free
di alcune variabili e lasciare intoccate le altre)
*/
void	ft_free_shell(t_shell *shell)
{
	if (shell->line)
		ft_free((void **)&(shell->line));
	if (shell->fd_input)
		ft_free((void **)&(shell->fd_input));
	if (shell->fd_output)
		ft_free((void **)&(shell->fd_output));
	if (shell->lvls)
		ft_free((void **)&(shell->lvls));
	if (shell->parsed)
		ft_free_mat((void ***)&shell->parsed);
	if (shell->pipex.pipe)
		ft_free((void **)&(shell->pipex.pipe));
	if (shell->envp)
		ft_free_mat((void ***)&(shell->envp));
	if (shell->list)
		ft_free_list(&shell->list);
	ft_free_red(shell);
}

/*
DESCRIPTION
this function does the free of all the variables in t_shell and *in base a
todo esce dal programma o ritorna un numero*
*/
int	ft_die(t_shell *shell, int todo, int code)
{
	ft_free_shell(shell);
	rl_clear_history();
	if (todo == 1)
		exit(code);
	else
		return (code);
}