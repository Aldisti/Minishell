#include "../minishell.h"

void	ft_redirection(t_shell *shell)
{
	int	i;
	int	ret;

	if (ft_allocate_rarray(shell))
		exit(1); // ft_die(); Error: memory error
	i = 0;
	while (shell->parsed[i])
	{
		if (ft_red_check(shell->parsed[i]))
			exit(4); // ft_die(); Error: unexpected token/invalid operator
		i++;
	}
	i = 0;
	while (shell->parsed[i])
	{
		ret = ft_apply_red(shell, i);
		if (ret == 1)
			exit(1); // ft_die(); Error: memory error
		else if (ret == 2 && ++i)
			continue;
		ft_replace_red(shell, i);
		i++;
	}
	if (ft_fill_red(shell))
		exit(1); // ft_die(); Error: memory error
}
