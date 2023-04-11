/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 07:54:04 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/07 15:45:17 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	if (!line)
		return ;
	i = 0;
	while (line[i])
	{
		ft_quotes_check(line, &i);
		if (!line[i])
			return ;
		if (ft_in(line[i], old))
			line[i] = new;
		i++;
	}
}

int	ft_lvls(t_shell *shell)
{
	char	*line;

	ft_free((void **) &shell->lvls);
	line = ft_joiner(shell->parsed, 0);
	ft_free_mat((void ***) &shell->parsed);
	if (!line)
		return (ft_die(shell, 1, 12));
	shell->n_cmds = ft_count_cmds(line);
	shell->lvls = (int *)ft_calloc(sizeof(int), shell->n_cmds);
	if (!shell->lvls)
		return (ft_die(shell, 1, 12));
	ft_set_lvls(line, shell->lvls);
	ft_replace(line, "()", ' ');
	shell->parsed = ft_parser(shell, line, "|&");
	ft_free((void **) &line);
	if (!shell->parsed)
		return (ft_die(shell, 1, 12));
	return (0);
}
