/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 07:47:21 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/07 15:31:19 by gpanico          ###   ########.fr       */
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
		ft_die(shell, 1, 12);
	shell->parsed[n_cmd][i] = tmp;
	*ind = i - 1;
	return (0);
}

int	ft_remove_quotes(t_shell *shell, char **line)
{
	char	*new_line;
	int		i;
	int		j;

	if (!(*line))
		return (0);
	i = ft_strlen_without(*line, "\'\"");
	if (i != (int) ft_strlen(*line))
	{
		new_line = (char *)ft_calloc(sizeof(char), i + 1);
		if (!new_line)
			ft_die(shell, 1, 12);
		i = 0;
		j = 0;
		while ((*line)[i])
		{
			if (!ft_in((*line)[i], "\'\""))
				new_line[j++] = (*line)[i];
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
				ft_die(shell, 1, 12);
			else if (ret == 2)
				return (2);
			else if (ft_output_red(shell, n_cmd, &i))
				ft_die(shell, 1, 12);
			else if (ft_append_red(shell, n_cmd, &i))
				ft_die(shell, 1, 12);
			else if (ft_hdoc_red(shell, n_cmd, &i))
				ft_die(shell, 1, 12);
		}
		i++;
	}
	return (0);
}
