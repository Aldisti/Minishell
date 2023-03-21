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
	if (!new_p)
		return (NULL);
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

int	ft_in(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strndup(const char *str, int dim)
{
	char	*new_str;
	int	i;

	new_str = (char *)ft_calloc(sizeof(char) * (dim + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i] && i < dim)
	{
		new_str[i] = str[i];
		i++;
	}
	return (new_str);
}

int	ft_token_word(char **line, char ***token, int *dim, int *flag)
{
	int	i;

	i = 0;
	while ((*line)[i] && !ft_in((*line)[i], METACHR))
	{
		if ((*line)[i] == ''')
		{
			while ((*line)[i] && (*line)[i] != ''')
				i++;
			if (!(*line)[i])
				return (1);
		}
		else if ((*line)[i] == '"')
		{
			while ((*line)[i] && (*line)[i] != '"')
				i++;
			if (!(*line)[i])
				return (1);
		}
		i++;
	}
	*token = (char **)ft_realloc((void *)(*token), sizeof(char **), *dim, *dim + 1);
	*dim = *dim + 1;
	if (!(*token))
		exit(1); //ft_die();
	*(token)[*dim - 2] = ft_strndup(*line, i);
	if (!(*token)[*dim - 2])
		exit(1); //ft_die();
	i = 0;
	*line = *line + i;
	if ((*line)[i])
		*flag = 1;
	return (0);
}

int	ft_token_metachr(char **line, char ***token, int *dim, int *flag)
{
	int	i;

	i = 0;
	while ((*line)[i] && ft_in((*line)[i], METACHR))
	{
		if ((*line)[i] == ''')
		{
			while ((*line)[i] && (*line)[i] != ''')
				i++;
			if (!(*line)[i])
				return (1);
		}
		else if ((*line)[i] == '"')
		{
			while ((*line)[i] && (*line)[i] != '"')
				i++;
			if (!(*line)[i])
				return (1);
		}
		i++;
	}
	*token = (char **)ft_realloc((void *)(*token), sizeof(char **), *dim, *dim + 1);
	*dim = *dim + 1;
	if (!(*token))
		exit(1); //ft_die();
	*(token)[*dim - 2] = ft_strndup(*line, i);
	if (!(*token)[*dim - 2])
		exit(1); //ft_die();
	i = 0;
	*line = *line + i;
	if ((*line)[0])
		*flag = 0;
	return (0);
}

char	**ft_token(t_shell shell)
{
	char	**token;
	int		dim;
	int		flag;
//	int		i;

	token = (char **)ft_calloc(1, sizeof(char *));
	if (!token)
		exit(1); //ft_die();
	dim  = 1;
//	i = 0;
	flag = 0;
	if (ft_in(shell.line[0], METACHR))
		flag = 1;
	while (shell.line[0])
	{
		if (!flag)
		{
//			while (shell.line[i] && !ft_in(shell.line[i], METACHR))
//				i++;
//			token = (char **)ft_realloc((void *)token, sizeof(char **), dim, ++dim);
//			if (!token)
//				exit(1); //ft_die();
//			token[dim - 2] = ft_strndup(shell.line, i);
//			if (!token[dim - 2])
//				exit(1); //ft_die();
//			shell.line = shell.line + i;
//			i = 0;
//			if (shell.line[i])
//				flag = 1;
			if (ft_token_word(&shell.line, &token, &dim, &flag))
				exit(2); //ft_die(); unsuccesful operation, quotes unclosed
		}
		else
		{
//			while (shell.line[i] && ft_in(shell.line[i], METACHR))
//				i++;
//			token = (char **)ft_realloc((void *)token, sizeof(char **), dim, ++dim);
//			if (!token)
//				exit(1); //ft_die();
//			token[dim - 2] = ft_strndup(shell.line, i);
//			if (!token[dim - 2])
//				exit(1); //ft_die();
//			shell.line = shell.line + i;
//			i = 0;
//			if (shell.line[i])
//				flag = 0;
			if (ft_token_metachr(&shell.line, &token, &dim, &flag))
				exit(2); //ft_die(); unsuccesful operation, quotes unclosed
		}
	}
	return (token);
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
