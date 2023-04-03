/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 07:47:21 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/03 07:52:34 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_fd(t_shell *shell, int n_cmd, int ind, char type)
{
	if (!ind)
	{
		if (ft_in(type, "ih"))
			return (0);
		else if (ft_in(type, "oa"))
			return (1);
	}
	ind--;
	while (ind > 0 && ft_isdigit(shell->parsed[n_cmd][ind]))
		ind--;
	if (!ft_in(shell->parsed[n_cmd][ind], " 0123456789")
		|| ft_check_space(shell->parsed[n_cmd], ind))
	{
		if (ft_in(type, "ih"))
			return (0);
		else if (ft_in(type, "oa"))
			return (1);
	}
	return (ft_atoi(&shell->parsed[n_cmd][ind]));
}

void	ft_put_filename(t_shell *shell, int n_cmd, char *dup, char type)
{
	if (type == 'a')
		shell->red.afiles[n_cmd / 2] = dup;
	else if (type == 'o')
		shell->red.outfiles[n_cmd / 2] = dup;
	else
		shell->red.infiles[n_cmd / 2] = dup;
}

int	ft_get_filename(t_shell *shell, int n_cmd, int *ind, char type)
{
	int		i;
	char	tmp;
	
	while (shell->parsed[n_cmd][*ind] == ' ')
		(*ind)++;
	i = *ind;
	while (shell->parsed[n_cmd][i] && shell->parsed[n_cmd][i] != ' ')
	{
		if (ft_in(shell->parsed[n_cmd][i], "\'\""))
			ft_quotes_check(shell->parsed[n_cmd], &i);
		else
			i++;
	}
	tmp = shell->parsed[n_cmd][i];
	shell->parsed[n_cmd][i] = 0;
	ft_put_filename(shell, n_cmd, ft_strdup(&shell->parsed[n_cmd][*ind]),
		type);
	if (ft_check_fn_status(shell, n_cmd, type))
		return (1); // Error: memory error
	shell->parsed[n_cmd][i] = tmp;
	*ind = i - 1;
	return (0);
}

int	ft_remove_quotes(char **line)
{
	char	*new_line;
	int		i;
	int		j;

	i = ft_strlen_without(*line, "\'\"");
	if (i != ft_strlen(*line))
	{
		new_line = (char *)ft_calloc(sizeof(char), i + 1);
		if (!new_line)
			return (1); // Error: memory error
		i = 0;
		j = 0;
		while ((*line)[i])
		{
			if (!ft_in((*line)[i], "\'\""))
			{
				new_line[j] = (*line)[i];
				j++;
			}
			i++;
		}
		ft_free((void **) line);
		*line = new_line;
	}
	return (0);
}

int	ft_apply_red(t_shell *shell, int n_cmd)
{
	int	i;
	int	ret;

	i = 0;
	while (shell->parsed[n_cmd][i])
	{
		ft_quotes_check(shell->parsed[n_cmd], &i);
		if (ft_in(shell->parsed[n_cmd][i], "><"))
		{
			ret = ft_input_red(shell, n_cmd, &i);
			if (ret == 1)
				return (1); // Error: memory error
			else if (ret == 2)
				return (2); // Error: cannot read file
			else if (ft_output_red(shell, n_cmd, &i))
				return (1); // Error: memory error
			else if (ft_append_red(shell, n_cmd, &i))
				return (1); // Error: memory error
			else if (ft_hdoc_red(shell, n_cmd, &i))
				return (1); // Error: memory error
		}
		i++;
	}
	return (0);
}
