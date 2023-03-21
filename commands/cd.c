/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:20:02 by marco             #+#    #+#             */
/*   Updated: 2023/03/20 21:11:44 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	strlen_cd(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		;
	return (i);
}

int	update_oldpwd(char **envp, char *str)
{
	int	i;

	i = -1;
	while (ft_strncmp(envp[++i], "OLDPWD", 6))
		;
	envp[i] = ft_strjoin("OLDPWD=", str);
	return (i);
}

void	cd(char **argv, char **envp)
{
	char	*str;
	char	*user;
	char	*oldpwd;
	int		envp_id;

	user = getenv("USER");
	oldpwd = pwd();
	if (!argv[1] || (!ft_strncmp("~", argv[1], 1) && strlen_cd(argv[1]) == 1))
	{
		str = pwd();
		while (ft_strncmp(user, ft_strrchr(str, '/') + 1, strlen_cd(user)))
		{
			free(str);
			str = pwd();
			chdir("..");
		}
		free(str);
		chdir(user);
	}
	else if (!ft_strncmp("--", argv[1], 2) && strlen_cd(argv[1]) == 2)
	{
		if (chdir(getenv("OLDPWD")) == -1)
		{
			free(oldpwd);
			return ;
		}
	}
	else if (argv[1])
	{
		if (chdir(argv[1]) == -1)
		{
			printf("%s: directory inesistente\n", argv[1]);
			free(oldpwd);
			return ;
		}
	}
	update_oldpwd(envp, oldpwd);
	free(oldpwd);
}