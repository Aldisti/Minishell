/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:34:49 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/22 17:07:10 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

int	shell_errno = 0;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				unset;
	struct s_env	*next;
	struct s_env	*level;
}	t_env;

typedef struct s_pipex
{
	int		*pipe;
	int		pipe_count;
	int		cmd_count;
	int		infile_fd;
	int		outfile_fd;
	int		original_stdout;
	pid_t	*pid;
	int		cmd_i;
	char	**paths;
}	t_pipex;

typedef struct s_shell
{
	char	**parsed;
	char	*line;
	int		*fd_input;
	int		*fd_output;
	t_env	*env;
	t_pipex	*pipex;
}	t_shell;

// funzioni del main (devono essere cosi)
void	ft_init(t_shell *env, char **envp);
char	**ft_parser(t_shell *shell, char *set);
char	**ft_expansion(t_shell *shell);
char	**ft_redirection(t_shell *shell);
int		ft_executor(t_shell *shell);
void	ft_catch_error(t_shell *shell);

//	pipex

//	Utils
void	*ft_calloc(size_t num, size_t dim);
int		ft_isspace(int c);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
