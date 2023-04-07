/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:20:02 by marco             #+#    #+#             */
/*   Updated: 2023/03/29 12:37:28 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	update_oldpwd(t_shell *shell, char *str, int lvl)
{
	t_env	*env;

	(void) lvl;
	env = ft_search_in_list(shell->list, "OLDPWD", 0); //shell->lvls[lvl]
	// printf("he%s\n", env->value);
	free(env->value);
	env->value = ft_strdup(str);
}
//argv = shell.parserd

void	cd(t_shell *shell, char **cmd, int lvl)
{
	t_env	*env;
	char	*oldpwd;

	(void) lvl;
	oldpwd = pwd();
	env = ft_search_in_list(shell->list, "HOME", 0);//shell->lvls[lvl]
	if (!cmd[1])
		chdir(env->value);
	else if (!ft_strncmp("-", cmd[1], 1) && ft_strlen(cmd[1]) == 1)
	{
		env = ft_search_in_list(shell->list, "OLDPWD", 0);//shell->lvls[lvl
		if (chdir(env->value) == -1)
		{
			free(oldpwd);
			return ;
		}
	}
	else if (cmd[1])
	{
		if (chdir(cmd[1]) == -1)
		{
			printf("%s: directory inesistente\n", cmd[1]);
			free(oldpwd);
			return ;
		}
	}
	update_oldpwd(shell, oldpwd, 1);//shell->lvls[lvl]
	free(oldpwd);
}
