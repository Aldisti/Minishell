#include "minishell.h"

void	*ft_realloc(void *p, size_t size, int dim, int new_dim)
{
	char		*new_p;
	size_t		i;

	new_p = (char *)malloc(size * new_dim);
	if (!new_p)
		return (NULL);
	i = 0;
	while (i < size * new_dim)
	{
		if (i < size * dim)
			new_p[i] = ((char *) p)[i];
		else
			new_p[i] = 0;
		i++;
	}
	free(p);
	return ((void *) new_p);
}

int	ft_in(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char **ft_extract_word(char **parsed, int *dim, int *i, char **line)
{
	if (*i)
	{
		parsed = (char **)ft_realloc(parsed, sizeof(char *), *dim, *(dim) + 1);
		if (!parsed)
			return (NULL); // ft_die(); Error: memory error
		*(dim) = *(dim) + 1;
		parsed[*(dim) - 2] = ft_substr(*line, 0, *i);
		if (!parsed[*(dim) - 2])
			return (NULL); // ft_die(); Error: memory error
		*line = *line + *i;
		*i = 0;
		return (parsed);
	}
	else
		return (parsed);
}

char	**ft_parser(t_shell shell)
{
	int	dim;
	int	i;
	char	**parsed;

	parsed = (char **)ft_calloc(sizeof(char *), 1);
	if (!parsed)
		exit(1); // ft_die(); Error: memory error
	dim = 1;
	i = 0;
	while (shell.line[i])
	{
		while (shell.line[i] && !ft_in(shell.line[i], "|&"))
		{
			if (shell.line[i] == '\'')
			{
				i++;
				while (shell.line[i] && shell.line[i] != '\'')
					i++;
				if (!shell.line[i])
					exit(1); // ft_die(); Error: unclosed quotes
			}
			else if (shell.line[i] == '\"')
			{
				i++;
				while (shell.line[i] && shell.line[i] != '\"')
					i++;
				if (!shell.line[i])
					exit(1); // ft_die(); Error: unclosed quotes
			}
			i++;
		}
		parsed = ft_extract_word(parsed, &dim, &i, &shell.line);
		if (!parsed)
			exit(1); // ft_die(); Error: memory error
		while (shell.line[i] && ft_in(shell.line[i], "|&"))
			i++;
		parsed = ft_extract_word(parsed, &dim, &i, &shell.line);
		if (!parsed)
			exit(1); // ft_die(); Error: memory error
	}
	return (parsed);
}
