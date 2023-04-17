#include "../minishell.h"

char	**ft_take_paths(t_shell *shell, int id)
{
	t_list	*node;
	t_env	*elem;
	char	**paths;

	node = ft_get_node(shell->list, "PATH=");
	elem = ft_get_env(node, shell->lvls[id]);
	if (!elem || !elem->value || elem->value[0] == 0)
	{
		paths = ft_split("/", ':');
		if (!paths)
			ft_die(shell, 1, 12);
		return (paths);
	}
	paths = ft_split(elem->value, ':');
	if (!paths)
		ft_die(shell, 1, 12);
	return (paths);
}

void	ft_exit_exec(t_shell *shell, char **argv, char **cmd, int type)
{
	ft_free_mat((void ***) &argv);
	ft_free_mat((void ***) &cmd);
	if (type == 0)
		ft_die(shell, 1, 0);
	else if (type == 1)
	{
		child_free(&shell->pipex, 0);
		ft_die(shell, 1, 1);
	}
	else if (type == 2)
		ft_die(shell, 1, 12);
	else if (type == 3)
	{
		child_free(&shell->pipex, 0);
		ft_die(shell, 1, 127);
	}
}
