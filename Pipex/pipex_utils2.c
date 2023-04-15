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
