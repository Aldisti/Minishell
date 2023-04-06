#include "../minishell.h"

/*
 * Description:	checks if the strings in parsed have
 * 		invalid operators.
 * Input:	the strings array.
 * Output:	returns an integer:
 * 			-0 if there are an invalid command;
 * 			-1 if there are invalid command.
*/
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
