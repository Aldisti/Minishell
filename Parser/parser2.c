/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:05:56 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/06 15:28:10 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Description:	parses the given string line creating an array
 * 		of strings divided by the characters in set; this 
 * 		function behaviour is like the ft_split one
 * 		(see 42 cursus: libft) but the splitting characters
 * 		are preserved in the array as strings between
 * 		the strings of splitted elements; furthermore
 * 		the function checks if there are unclosed parentheses
 * 		or quotes.
 * Input:	the pointer to shell structure (see minishell.h),
 * 		the line to be parsed and the splitting characters
 * 		given as a C string (i.e. null terminated
 * 		array of character).
 * Output:	returns the array of strings resulting by splitting;
 * 		if an error occurs returns a NULL pointer.
*/
char	**ft_parser(t_shell *shell, char *line, char *set)
{
	int		dim;
	int		i;
	char	**parsed;

	(void) shell;
	parsed = (char **)ft_calloc(sizeof(char *), 1);
	if (!parsed)
		exit(1); // ft_die(); Error: memory error
	dim = 1;
	i = 0;
	while (line[i])
	{
		while (line[i] && !ft_in(line[i], set))
			if (!ft_checks(line, &i))
				exit (2); // ft_die() Error: unclosed quotes/parentheses
		if (!i)
			while (line[i] && ft_in(line[i], set))
				i++;
		parsed = ft_extract_word(parsed, &dim, &i, &line);
		if (!parsed)
			exit(1); // ft_die(); Error: memory error
	}
	return (parsed);
}


/*
 * Description:	deletes all spaces at the beginning and at the ending
 * 		of each string in the array of strings 'shell->parsed'
 * 		(see minishell.h)
 * Input:	pointer struct shell (see minishell.h).
 * Output:	returns an integer:
 * 			-1 if a memory error occurs;
 * 			-0 if there aren't errors
*/
int	ft_delete_spaces(t_shell *shell)
{
	char	*trimmed;
	int		i;

	i = 0;
	while (shell->parsed[i])
	{
		trimmed = ft_strtrim(shell->parsed[i], " ");
		if (!trimmed)
			return (1);
		ft_free((void **) &shell->parsed[i]);
		shell->parsed[i] = trimmed;
		i++;
	}
	return (0);
}

/*
 * Description:	checks if there are unclosed parentheses in the line
 * Input:	the string to be checked
 * Output:	returns an integer:
 * 			-1 if the parentheses are unclosed;
 * 			-0 if the parentheses are closed;
*/
int	ft_check_multi_par(char *line)
{
	int	i;
	int	par_count;
	int	count;
	int	index;

	i = 0;
	count = 0;
	par_count = 0;
	index = 0;
	while (line[i])
	{
		if (!par_count && index)
			count++;
		if (line[i] == '(')
		{
			index++;
			par_count++;
		}
		else if (line[i] == ')')
			par_count--;
		i++;
	}
	if (count != 1 && count)
		return (1);
	return (0);
}

/*
 * Description:	checks if the operators in the parsed strings 
 * 		are valid (i.e. '|' '&' '||' '&&').
 * Input:	the strings array.
 * Output:	returns an integer:
 * 			-0 if there is an invalid operator;
 * 			-1 if the operators are valid.
*/
int	ft_valid_operators(char **parsed)
{
	int	i;
	int	j;

	i = 0;
	while (parsed[i])
	{
		j = 0;
		while (parsed[i][j])
		{
			ft_quotes_check(parsed[i], &j);
			if (ft_in(parsed[i][j], "|&"))
			{
				if (ft_strlen_until(&parsed[i][j], " \n\t<>()") > 2)
					return (0);
				if (ft_strncmp(&parsed[i][j], "|", 1) &&
					ft_strncmp(&parsed[i][j], "||", 2) &&
					ft_strncmp(&parsed[i][j], "&&", 2))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

/*
 * Description: checks if there are errors in the commands string
 * 		checks done:
 * 			-delete all starting and ending spaces;
 * 			-the string must not begin with | or &;
 * 			-the operators in the string are valid (see above);
 * 			-there aren't invalid commands (e.g. cmd1|  |cmd2);
 * 			-there aren't closed parentheses.
 * Input:	pointer to shell structure (see minishell.h).
 * Output:	na.
*/
void	ft_parser_checks(t_shell *shell)
{
	int	i;

	if (ft_delete_spaces(shell))
		exit(1); // ft_die; Error: memory error
	if (!shell->parsed)
		exit(1); // ft_die(); Error: memory error
	if (ft_in(shell->parsed[0][0], "&|"))
		exit(4); // ft_die(); Error: invalid command
	if (!ft_valid_operators(shell->parsed))
		exit(5); // ft_die(); Error: invalid operator
	if (!ft_valid_command(shell->parsed))
		exit(4); // ft_die(); Error: invalid command
	i = 0;
	while (shell->parsed[i])
	{
		if (ft_check_multi_par(shell->parsed[i]))
			exit(4); // ft_die(); Error: invalid command
		i++;
	}
}
