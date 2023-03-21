/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:34:49 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/21 18:27:57 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char	**parsed;
	char	*line;
	int		n_cmd;
	int		*n_pipe;
	t_env	*env;
}	t_shell;

//	parser
char	**ft_parser(char *str);
//	executor
int		ft_executor(char **parsed);
//	exec_utils
char	**ft_getcmd(char **parsed);
char	*ft_find_cmd(char *cmd, char **paths);
char	*ft_execute_cmd(char **cmd);
//	Utils
void	*ft_calloc(size_t num, size_t dim);
int		ft_isspace(int c);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
