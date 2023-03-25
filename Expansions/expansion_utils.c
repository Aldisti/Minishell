

#include "../minishell.h"

//	return: from a string and an index i, this function returns the level of
//		subshell at the index i
int	ft_getlvl(char *str, int i)
{
	int	j;
	int	brackets;

	j = -1;
	while (++j < i)
	{
		if (!ft_getquotes(str, j) && str[j] == '(')
			brackets++;
		if (!ft_getquotes(str, j) && str[j] == ')')
			brackets--;
	}
	return (brackets);
}

//	return: from a string [str] and an index [i] this function tells if i is
//		inside some quotes then tells the type of the quotes then returns 0
//	return types
//	[0] -> out of quotes
//	[1] -> inside single quotes
//	[2] -> inside double quotes
int	ft_getquotes(char *str, int i)
{
	int	quotes;
	int	j;

	j = -1;
	quotes = 0;
	while (++j < i)
	{
		if (str[i] == '\'' && !quotes)
			quotes = 1;
		else if (str[i] == '\"' && !quotes)
			quotes = 2;
		else if (str[i] == '\'' && quotes == 1)
			quotes = 0;
		else if (str[i] == '\"' && quotes == 2)
			quotes = 0;
	}
	return (quotes);
}