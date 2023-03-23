/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:34:49 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/23 09:55:11 by gpanico          ###   ########.fr       */
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

/*
typedef struct s_env
{
	char			*name;
	char			*value;
	int				unset;
	struct s_env	*next;
	struct s_env	*level;
}	t_env;
*/

typedef struct s_env
{
	char			*name;
	char			*value;
	int				set;
	int				level;
	struct s_env	*next;
}	t_env;

typedef struct s_list
{
	t_env			*content;
	struct s_list	*next;
}	t_list;

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

//	Init
//	set_env
t_list	*ft_env_set(char **envp);
char	*ft_get_name(const char *str);
char	*ft_get_value(const char *str);

//	Parser
//	parser
int		ft_in(char c, char *set);
int		ft_quotes_check(char *line, int *i);
char	**ft_extract_word(char **parsed, int *dim, int *i, char **line);

//	Pipex
// 	pipex
int		child_proc(t_pipex *pipex, char **argv, int child_id);
int		pipex_init(t_pipex *pipex, int argc, char **argv);
int		pipex(t_shell *shell, char **argv);
char	**rm_pipe_n_space(char **strs);
void	execute_command(char **cmd);
//	pipex_utils
void	ft_free(char **strs);
void	child_free(t_pipex *pipex, char **cmd);
int		create_pipes(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
void	my_dup(int first, int second);
//	command
char	**path_n_command(t_pipex *pipex, char **argv, int el);
char	**get_cmd(t_pipex *pipex, char **argv, int child_id);
void	command_not_found(t_pipex *pipex);
char	*path_checker(t_pipex *pipex);
int		prepare_strs(char **strs);
// command_parser
char	**ft_extract_word_command(char **parsed, int *dim, int *i, char **line);
void	*mft_realloc(void *p, size_t size, int dim, int new_dim);
int		ft_quotes_check_command(char *line, int	*i);
char	**command_parser(char *str, char *set);
int		ft_in_command(char c, char *set);
//	trim_strs
void	trim_strs(char **strs);

//	Utils
void	*ft_calloc(size_t num, size_t dim);
void	*ft_realloc(void *p, size_t size, int dim, int new_dim);
int		ft_isspace(int c);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *str, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);

#endif
