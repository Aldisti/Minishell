#include "minishell.h"

char	**ft_parser(char *str)
{
	char	**parsed;
	int		i;
	int		j;
	int		len;
	int		quote;
	int		space;
	int		bracket;
	int		dollar;

	parsed = (char **) calloc (15, sizeof(char *));
	if (!parsed)
		return (0);
	i = -1;
	j = 0;
	len = 0;
	space = 0;
	quote = 0;
	bracket = 0;
	dollar = 0;
	while (str[++i])
	{
		if (str[i] == 39 || str[i] == 34) // [']:39 ["]:34
		{
			if (quote == 1 && str[i] == 39)
				quote = 0;
			else if (quote == 2 && str[i] == 34)
				quote = 0;
			else if (!quote && str[i] == 39)
				quote = 1;
			else if (!quote && str[i] == 34)
				quote = 2;
		}
		if (str[i] == '$' && str[i + 1] == '(')
			dollar = 1;
		if ((str[i] == '(' || str[i] == ')') && dollar)
		{
			if (str[i] == '(')
				bracket++;
			else if (str[i] == ')')
				bracket--;
			if (!bracket)
				dollar = 0;
		}
		if (!ft_isspace(str[i]) && space)
			space = 0;
		if ((ft_isspace(str[i]) && !space && !quote && !bracket) || (len && !str[i + 1]))
		{
			parsed[j++] = ft_substr(str, i - len, len + (str[i + 1] == 0 && !ft_isspace(str[i])));
			space = 1;
			len = 0;
		}
		else
			len++;
	}
	if (quote)
		printf("Error\nmissing closing quote\n");
	if (bracket)
		printf("Error\nmissing bracket\n");
	return (parsed);
}