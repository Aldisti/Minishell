/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:20:02 by marco             #+#    #+#             */
/*   Updated: 2023/03/24 11:53:52 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	get_oldpwd_i(char **envp)
{
	int		i;

	i = -1;
	while (ft_strncmp(envp[++i], "OLDPWD", 6))
		;
	return (i);
}

int	update_oldpwd(char **envp, char *str)
{
	int		i;
	char	*temp;

	i = get_oldpwd_i(envp);
	envp[i] = ft_strjoin("OLDPWD=", str);
	return (i);
}

void	cd(char **argv, char **envp)
{
	char	*str;
	char	*user;
	char	*oldpwd;
	int		envp_id;
	char	**cmd;

	oldpwd = pwd();
	cmd = ft_split(argv[0], ' ');
	user = getenv("USER");
	if (!cmd[1] || (!ft_strncmp("~", cmd[1], 1) && ft_strlen(cmd[1]) == 1))
	{
		str = pwd();
		while (ft_strncmp(user, ft_strrchr(str, '/') + 1, ft_strlen(user)))
		{
			free(str);
			str = pwd();
			chdir("..");
		}
		free(str);
		chdir(user);
	}
	else if (!ft_strncmp("-", cmd[1], 1) && ft_strlen(cmd[1]) == 1)
	{
		if (chdir(ft_strrchr(envp[get_oldpwd_i(envp)], '=') + 1) == -1)
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
	update_oldpwd(envp, oldpwd);
	free(oldpwd);
}
