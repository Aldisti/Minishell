/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:34:49 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/27 09:37:31 by gpanico          ###   ########.fr       */
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

# ifndef METACHARS
#  define METACHARS " \n\t|&<>()"
# endif

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
	t_list	*list;
	t_pipex	pipex;
}	t_shell;

// funzioni del main (devono essere cosi)
// void	ft_init(t_shell *env, char **envp);
// char	**ft_parser(t_shell *shell, char *set);
// char	**ft_redirection(t_shell *shell);
// int		ft_executor(t_shell *shell);
// void	ft_catch_error(t_shell *shell);



//	Init
//	env_set
t_list	*ft_env_set(char **envp);
char	*ft_get_name(const char *str);
char	*ft_get_value(const char *str);



//	Parser
//	parser
int		ft_in(char c, char *set);
int		ft_checks(char *line, int *i);
int		ft_quotes_check(char *line, int *i);
int		ft_parenthesis_check(char *line, int *i);
char	**ft_extract_word(char **parsed, int *dim, int *i, char **line);
//	parser2
char	**ft_parser(t_shell *shell, char *set);
int		ft_delete_spaces(t_shell *shell);
int		ft_check_multi_par(char *line);
void	ft_parser_checks(t_shell *shell);


//	espansion
char	**ft_expand_all(t_shell *shell);
char	*ft_expansion(t_shell *shell, char *str);
char	*ft_check_quote(t_list *list, char *str, int *i);
char	*ft_resolve_expansion(t_list *list, char *str, int lvl);



//	Commands
//	cd
int		get_oldpwd_i(char **envp);
void	cd(char **argv, char **envp);
int		update_oldpwd(char **envp, char *str);
//	pwd
void	print_pwd(void);
char	*pwd(void);



//	Pipex
//	pipex
char	**line_filter(char **strs);
void	execute_command(char **cmd);
int		pipex(t_shell *shell, char **argv);
int		pipex_init(t_pipex *pipex, int argc, char **argv);
int		child_proc(t_pipex *pipex, char **argv, int child_id);
//	pipex_utils
void	my_dup(t_pipex *pipex, int id, int mode);
int		create_pipes(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
int		prepare_strs(char **strs);
void	trim_strs(char **strs);
//	command
char	**get_cmd(t_pipex *pipex, char *str);
char	*path_checker(t_pipex *pipex, char *str);
void	get_cmd_loop(t_pipex *pipex, char *temp, char **command);
//	command_parser
char	**ft_extract_word_command(char **parsed, int *dim, int *i, char **line);
int		ft_quotes_check_command(char *line, int	*i);
char	**command_parser(char *str, char *set);
//	free
void	ft_free(void **strs);
void	ft_free_mat(void ***mat_addr);
void	child_free(t_pipex *pipex, char **cmd);



//	Utils
char	*ft_itoa(int n);
int		ft_isspace(int c);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_joiner(char **tab, int n);
char	*ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t num, size_t dim);
char	*ft_strrchr(const char *str, int c);
void	ft_lstadd_back(t_list **lst, t_list *new);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_countn(const char *str, const char c, int n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
t_env	*ft_search_in_list(t_list *list, char *name, int lvl);
void	*ft_realloc(void *p, size_t size, int dim, int new_dim);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
