#include "../minishell.h"

void	ft_set_rarray(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->n_cmds)
	{
		shell->red.fdout[i] = 1;
		shell->red.fda[i] = 1;
		i++;
	}
}

int	ft_allocate_rarray(t_shell *shell)
{
	shell->red.infiles = (char **)ft_calloc(sizeof(char *),
				shell->n_cmds + 1);
	if (!shell->red.infiles)
		return (1); // ft_die(); Error: memory error
	shell->red.outfiles = (char **)ft_calloc(sizeof(char *),
				shell->n_cmds + 1);
	if (!shell->red.outfiles)
		return (1); // ft_die(); Error: memory error
	shell->red.afiles = (char **)ft_calloc(sizeof(char *),
				shell->n_cmds + 1);
	if (!shell->red.afiles)
		return (1); // ft_die(); Error: memory error
	shell->red.fdin = (int *)ft_calloc(sizeof(int), shell->n_cmds);
	if (!shell->red.fdin)
		return (1); // ft_die(); Error: memory error
	shell->red.fdout = (int *)ft_calloc(sizeof(int), shell->n_cmds);
	if (!shell->red.fdout)
		return (1); // ft_die(); Error: memory error
	shell->red.fda = (int *)ft_calloc(sizeof(int), shell->n_cmds);
	if (!shell->red.fda)
		return (1); // ft_die(); Error: memory error
	ft_set_rarray(shell);
	return (0);
}
