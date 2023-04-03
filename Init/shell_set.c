
#include "../minishell.h"

void	ft_shell_set(t_shell *shell)
{
	shell->line = 0;
	shell->parsed = 0;
	shell->envp = 0;
	shell->fd_input = 0;
	shell->fd_output = 0;
	shell->lvls = 0;
	shell->pipex.pipe = 0;
	shell->pipex.pid = 0;
	shell->pipex.paths = 0;
	ft_signals_set(shell);
	shell->envp = list_convert(shell->list);
	if (!shell->envp)
		exit(1); //	ft_die(&shell);
}