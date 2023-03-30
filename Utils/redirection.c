#include "../minishell.h"

typedef struct s_elem
{
	char	**infiles;
	char	**outfiles;
	char	**afiles;
	int		*fdin;
	int		*fdout;
	int		*fda;
}	t_elem;

typedef struct s_relist
{
	t_elem			*content;
	struct s_relist	*next;
}	t_relist;

int	ft_serch(const char *str, const char *set)
{
	int	i;
	int	j;
	
	i = 0;
	while (str[i])
	{
		j = 0;
		while (set[j])
		{
			if (str[i] == set[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_expand_par(t_shell *shell)
{
	char	**new_parsed;

	shell->line = ft_joiner(shell->parsed, 0);
	ft_free_mat((void ***) &shell->parsed);
	shell->parsed = ft_parser(shell, shell->line, "|&()");
	for (int i = 0; shell->parsed[i]; i++)
		printf("%s\n", shell->parsed[i]);
}

/*
void	ft_set_red(t_shell *shell, char *frag)
{
	
}
*/

char **ft_redirection(t_shell *shell)
{
	char	**tmp_parsed;
	int	i;
	int	j;

	i = 0;
	ft_expand_par(shell);
	exit(1);
	/*
	while (shell->parsed[i])
	{
		shell->line = shell->parsed[i];
		tmp_parsed = ft_parser(shell->line, " ");
		if (!tmp_parsed)
			exit(1); // ft_die(); Error: memory error
		j = 0;
		while (tmp_parsed[j])
		{
			if (ft_search(tmp_parsed[j], "<>"))
			{
				ft_set_red(shell, frag);
				ft_set_del(tmp_parsed);
			}
			j++;
		}
		ft_free((void **) &shell->parsed[i]);
		shell_parsed[i] = ft_joiner(tmp_parsed);
		ft_free_mat((void ***) &tmp_parsed);
		i++;
	}
	*/
}
