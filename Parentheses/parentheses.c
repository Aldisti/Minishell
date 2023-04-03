#include "../minishell.h"

int	ft_count_cmds(char *line)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	while (line[i])
	{
		ft_quotes_check(line, &i);
		if (ft_in(line[i], "|&"))
		{
			n++;
			while (ft_in(line[i + 1], "|&"))
				i++;
		}
		i++;
	}
	return (n);
}

int	ft_update_lvl(char c, int lvl, int *array)
{
	if (c == '(')
		return (lvl + 1);
	else if (c == ')')
	{
		if (!array[0])
			array[0] = lvl;
		return (lvl - 1);
	}
	return (lvl);
}

void	ft_set_lvls(char *line, int *lvls)
{
	int	i;
	int	j;
	int	lvl;

	i = 0;
	j = 0;
	lvl = 0;
	while (line[i])
	{
		ft_quotes_check(line, &i);
		lvl = ft_update_lvl(line[i], lvl, &lvls[j]);
		if (ft_in(line[i], "|&"))
		{
			while (ft_in(line[i + 1], "|&"))
				i++;
			if (!lvls[j])
				lvls[j] = lvl;
			j++;
		}
		i++;
	}
}

void	ft_replace(char *line, char *old, char new)
{
	int	i;

	i = 0;
	while (line[i])
	{
		ft_quotes_check(line, &i);
		if (ft_in(line[i], old))
			line[i] = new;
		i++;
	}
}

int	ft_lvls(t_shell *shell)
{
	char	*line;

	// tmp
	shell->lvls = NULL;
	ft_free((void **) &shell->lvls);
	// tmp
	line = ft_joiner(shell->parsed, 0);
	if (!line)
		return (1); // ft_die(); Error: memory error
	ft_free_mat((void ***) &shell->parsed);
	shell->n_cmds = ft_count_cmds(line);
	shell->lvls = (int *)ft_calloc(sizeof(int), shell->n_cmds);
	if (!shell->lvls)
		return (1); // ft_die(); Error: memory error
	ft_set_lvls(line, shell->lvls);
	ft_replace(line, "()", ' ');
	shell->parsed = ft_parser(shell, line, "|&");
	if (!shell->parsed)
		return (1); // ft_die(); Error: memory error
	ft_free((void **) &line);
	return (0);
}
