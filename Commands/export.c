/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afraccal <afraccal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:28:20 by afraccal          #+#    #+#             */
/*   Updated: 2023/03/28 16:31:57 by afraccal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env(t_shell *shell, char *name, char *value)
{
	t_env	*save;
	t_env	*new;

	save = shell->list->content;
}

void	ft_export(t_shell *shell, char **argv)
{
	printf("export merda\n");
	int     i;
    char    *name;
    char    *value;
    char    **cmd;

	cmd = ft_split(argv[0], ' ');
	i = 0;
	if(cmd[1])
	{
		while (cmd[1][i] && cmd[1][i] != '=')
		{
			i++;
		}
		name = ft_substr(cmd[1], 0, i);
		i++;
		value = ft_strdup(cmd[1] + i);
		printf("name %s e value %s", name, value);
		add_env(shell, name, value);
	}
}
