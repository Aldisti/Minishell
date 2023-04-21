/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:20:02 by marco             #+#    #+#             */
/*   Updated: 2023/04/21 18:26:46 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
void	update_oldpwd(t_shell *shell, char *str, int lvl)

function used tu update the enviroment variable OLDPWD
that store the last known path before cd tha can be used 
we calling "CD -"
*/
void	update_oldpwd(t_shell *shell, int lvl)
{
	t_env	*env1;
	t_env	*env2;
	t_list	*new_lst;
	t_env	*new_env;

	env1 = ft_search_in_list(shell->list, "OLDPWD", lvl);
	if (!env1)
	{
		new_env = ft_env_new(ft_strdup("OLDPWD="), ft_strdup(""), lvl);
		new_lst = ft_lstnew(new_env);
		ft_lst_insert(&shell->list, new_lst);
		env1 = new_env;
	}
	env2 = ft_search_in_list(shell->list, "PWD", lvl);
	if (!env2)
		return ;
	ft_free((void **) &env1->value);
	env1->value = ft_strdup(env2->value);
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
int	what_to_do(t_shell *shell, int lvl, char **cmd)
{
	t_env	*env;

	if (!cmd[1])
	{
		env = ft_search_in_list(shell->list, "HOME", lvl);
		if (!env)
			return (fd_printf(2, "cd: HOME not set\n") * 0 + 1);
		chdir(env->value);
	}
	else if (!ft_strncmp("-", cmd[1], 1) && ft_strlen(cmd[1]) == 1)
	{
		env = ft_search_in_list(shell->list, "OLDPWD", lvl);
		if (!env)
			return (fd_printf(2, "cd: OLDPWD not set\n") * 0 + 1);
		if (chdir(env->value) == -1)
			return (ft_die_cd(env->value, cmd[1], 3));
		printf("%s\n", env->value);
	}
	else if (cmd[1])
		if (chdir(cmd[1]) == -1)
			return (ft_die_cd(NULL, cmd[1], 1));
	return (0);
}

/*
void	cd(t_shell *shell, char **cmd, int lvl)

this function emulate the origina cd operator, first
count the argument and if there are more than 2 return error
then parse the input and accordingly select what to do
*/
int	cd(t_shell *shell, char **cmd, int lvl)
{
	char	*oldpwd;
	int		val;

	if (args_count(cmd) > 2)
	{
		fd_printf(2, "cd: too many arguments\n");
		return (1);
	}
	ft_remove_quotes(shell, &cmd[1]);
	oldpwd = getcwd(0, 0);
	errno = 0;
	val = what_to_do(shell, lvl, cmd);
	if (val > 0)
	{
		ft_free((void **) &oldpwd);
		return (val);
	}	
	update_oldpwd(shell, lvl);
	ft_free((void **) &oldpwd);
	ft_update_pwd(shell, cmd[1], lvl);
	return (0);
}
