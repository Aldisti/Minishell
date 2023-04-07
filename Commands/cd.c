/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:20:02 by marco             #+#    #+#             */
/*   Updated: 2023/04/07 14:59:27 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
void	update_oldpwd(t_shell *shell, char *str, int lvl)

function used tu update the enviroment variable OLDPWD
that store the last known path before cd tha can be used 
we calling "CD -"
*/
void	update_oldpwd(t_shell *shell, char *str, int lvl)
{
	t_env	*env;

	env = ft_search_in_list(shell->list, "OLDPWD", lvl);
	free(env->value);
	env->value = ft_strdup(str);
}

/*
int	args_count(char **argv)

simple func that count the argument in a duoble
char pointer
*/
int	args_count(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i] && i < 3)
		i++;
	return (i);
}

/*
int	what_to_do(t_shell *shell, char *oldpwd, int lvl, char **cmd)

this is a kind of selector of things to do depending on the passed input
this version of cd can handle:
1. cd -
2. cd path
3. cd (no argument)
4. cd invalid path
*/
int	what_to_do(t_shell *shell, char *oldpwd, int lvl, char **cmd)
{
	t_env	*env;

	env = ft_search_in_list(shell->list, "HOME", lvl);
	if (!cmd[1])
		chdir(env->value);
	else if (!ft_strncmp("-", cmd[1], 1) && ft_strlen(cmd[1]) == 1)
	{
		env = ft_search_in_list(shell->list, "OLDPWD", lvl);
		if (chdir(env->value) == -1)
		{
			free(oldpwd);
			return (-1);
		}
	}
	else if (cmd[1])
	{
		if (chdir(cmd[1]) == -1)
		{
			write(2, "cd: no such file or directory\n", 27);
			free(oldpwd);
			return (-1);
		}
	}
	return (1);
}

/*
void	cd(t_shell *shell, char **cmd, int lvl)

this function emulate the origina cd operator, first
count the argument and if there are more than 2 return error
then parse the input and accordingly select what to do
*/
void	cd(t_shell *shell, char **cmd, int lvl)
{
	char	*oldpwd;

	if (args_count(cmd) > 2)
	{
		write(2, "cd: too many arguments\n", 24);
		return ;
	}
	oldpwd = pwd();
	if (what_to_do(shell, oldpwd, lvl, cmd) == -1)
		return ;
	update_oldpwd(shell, oldpwd, lvl);
	free(oldpwd);
}
