/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 08:15:08 by gpanico           #+#    #+#             */
/*   Updated: 2023/03/20 15:03:56 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(const char *str)
{
	int		len;
	char	*line;

	len = ft_strlen(str);
	write(1, str, len);
	line = get_next_line(0);
	return (line);
}

void	*ft_realloc(void *p, size_t size, int dim, int new_dim)
{
	char		*new_p;
	size_t		i;

	new_p = (char *)malloc(size * new_dim);
	i = 0;
	while (i < size * new_dim)
	{
		if (i < size * dim)
			new_p[i] = ((char *) p)[i];
		else
			new_p[i] = 0;
		i++;
	}
	free(p);
	return ((void *) new_p);
}

char	**ft_token(t_shell shell)
{
	char	**token;

	token = (char **) malloc(sizeof(char *) * 2);
	if (!token)
		exit(1); //ft_die();
	
}

int	main(void)
{
	t_shell	shell;
	char	*tmp;
	int		i;

	while (42)
	{
		shell.line = ft_readline("\033[1;36m$> \033[0m");
		add_history(shell.line);
		/*
		shell.token = ft_token(&shell);
		shell.parsed = ft_parser(&shell);
		shell.parsed = ft_expansion(&shell);
		shell.parsed = ft_redirection(&shell);
		ft_exec_commands(&shell);
		ft_exit_status_collector(&shell);
		*/
	}
	rl_clear_history();
	return (0);
}
