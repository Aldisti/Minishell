#include "../minishell.h"

void	*ft_die_readline(char **lines, int dim)
{
	int	i;

	i = 0;
	while (i < dim)
	{
		ft_free((void **) &lines[i]);
		i++;
	}
	ft_free((void **) &lines);
	return (NULL);
}

int	ft_end_with(char *line, char end)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (line[i])
	{
		if (line[i] == end && !found)
			found = 1;
		else if (found && !ft_in(line[i], " \t\n"))
			found  = 0;
		i++;
	}
	return (found);
}

char	*ft_read_again(char *prompt)
{
	char	*tmp;
	char	*line;

	tmp = readline(prompt);
	if (!tmp)
		return (NULL);
	line = ft_strjoin(" ", tmp);
	ft_free((void **) &tmp);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_readline(char *prompt)
{
	char	**lines;
	char	*line;
	int	dim;

	lines = NULL;
	dim = 2;
	lines = (char **) ft_realloc(lines, sizeof(char *), 0, dim);
	if (!lines)
		return (ft_die_readline(lines, dim));
	lines[dim - 2] = readline(prompt);
	if (!lines[dim - 2])
		return (ft_die_readline(lines, dim));
	while (ft_end_with(lines[dim - 2], '|'))
	{
		lines = (char **) ft_realloc(lines, sizeof(char *), dim, dim + 1);
		if (!lines)
			return (ft_die_readline(lines, dim));
		dim++;
		lines[dim - 2] = ft_read_again("> ");
		if (!lines[dim - 2])
			return (ft_die_readline(lines, dim));
	}
	line = ft_joiner(lines, 1);
	free(lines);
	return (line);
}
