#include "../minishell.h"

int	ft_valid_command(char **parsed)
{
	int	i;
	int	j;
	int	valid;

	valid = 0;
	i = 0;
	while (parsed[i])
	{
		j = 0;
		while (parsed[i][j])
		{
			if (!ft_in(parsed[i][j], " \n\t"))
				valid = 1;
			j++;
		}
		if (!valid)
			return (0);
		valid = 0;
		i++;
	}
	return (1);
}
