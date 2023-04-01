
#include "../minishell.h"

void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	tmp = 0;
	while (env)
	{
		tmp = env->next;
		if (env->name)
			ft_free((void **)&(env->name));
		if (env->value)
			ft_free((void **)&(env->value));
		if (env)
			ft_free((void **)&env);
		env = tmp;
	}
}

void	ft_free_list(t_list *list)
{
	t_list	*tmp;

	tmp = 0;
	while (list)
	{
		tmp = list->next;
		if (list->content)
			ft_free_env(list->content);
		if (list)
			ft_free((void **)&list);
		list = tmp;
	}
}

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
	if (shell->list)
	{
		ft_free_list(shell->list);
		shell->list = 0;
	}
}

/*
DESCRIPTION
this function does the free of all the variables in t_shell and *in base a
todo esce dal programma o ritorna un numero*
*/
int	ft_die(t_shell *shell, int todo, int code)
{
	ft_free_shell(shell);
	if (todo == 1)
		exit(code);
	else
		return (code);
}