/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:05:07 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/07 13:03:01 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_shell_errno;

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
			if (!ft_in(parsed[i][j], " \n\t()"))
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
/*
 * Syntax error:	invalid operator, unexpected token, 
 * 					unclosed quotes/parentheses.
*/
void	*ft_die_parser(t_shell *shell, char **parsed)
{
	ft_free_mat((void ***) &parsed);
	ft_die(shell, 0, 258);
	g_shell_errno = 258;
	return (NULL);
}