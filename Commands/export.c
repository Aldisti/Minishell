/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afraccal <afraccal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:28:20 by afraccal          #+#    #+#             */
/*   Updated: 2023/03/29 10:21:09 by afraccal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env(t_shell *shell, char *name, char *value)
{
	t_env	*save;
	t_env	*new;

	new = malloc (sizeof(shell->list->content));
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	while (shell->list->content)
	{
		printf("export merda\n");
		shell->list->content = shell->list->content->next;
	}
	printf("esco\n");
	save = shell->list->content;
	shell->list->content = new;
	new->next = save;
}

void	ft_export(t_shell *shell, char **argv)
{
	int     i;
    char    *name;
    char    *value;
    char    **cmd;

	printf("export merda\n");
	cmd = ft_split(argv[0], ' ');
	i = 0;
	if (!strncmp(argv[0], "export", 6) && !cmd[1])
	{
		while (shell->list)
		{
			printf("declare -x ");
			printf("%s", shell->list->content->name);
			printf("%s\n", shell->list->content->value);
			shell->list=shell->list->next;
		}
		return ;
	}
	if(!cmd[1] && ft_strchr(cmd[1], '='))
		return ;
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
		free(name);
		free(value);
	}
}
