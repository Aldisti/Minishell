/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:34:49 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/29 15:56:25 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

# ifndef METACHARS
#  define METACHARS " \n\t|&<>()"
# endif

// extern void	rl_replace_line(char *, int);
// extern void	rl_clear_history(void);

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
	struct sigaction	action_nothing;
	struct sigaction	action_int;
	struct sigaction	action_quit;
	struct termios		tty_attrs;
	char				**parsed;
	char				**envp;
	char				*line;
	int					*fd_input;
	int					*fd_output;
	int					*lvls;
	t_list				*list;
	t_pipex				pipex;
}	t_shell;

// funzioni del main (devono essere cosi)
// void	ft_init(t_shell *env, char **envp);
// char	**ft_parser(t_shell *shell, char *set);
// char	**ft_redirection(t_shell *shell);
// int		ft_executor(t_shell *shell);
// void	ft_catch_error(t_shell *shell);



//	Init
//	shell_set
void	ft_shell_set(t_shell *shell);
//	env_set
t_list	*ft_env_set(char **envp);
char	*ft_get_name(const char *str);
char	*ft_get_value(const char *str);
//	signals_set
void	ft_signals_set(t_shell *shell);



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
int		ft_valid_operators(char **parsed);



//	Expansions
//	expansion
char	*ft_expand_spec(t_shell *shell, char *str, int i);
char	*ft_expand_doll(t_shell *shell, char *str, int i);
char	*ft_expand_tilde(t_shell *shell, char *str, int i);
// char	*ft_expansion(t_shell *shell, char *str);
void	ft_expand_all(t_shell *shell);
//	expansion_utils
int		ft_getquotes(char *str, int i);
char	*ft_getname(char *str, int i);
int		ft_getlvl(char *str, int i);

//	Commands
//	cd
int		get_oldpwd_i(char **envp);
void	cd(t_shell *shell, char **cmd, int lvl);
void	update_oldpwd(t_shell *shell, char *str, int lvl);
//	pwd
void	print_pwd(void);
char	*pwd(void);
// env
void	env(t_shell	*shell);



//	Signals
//	signals
void	ft_does_nothing(int signum);
void	ft_handle_quit(int signum);
void	ft_handle_int(int signum);


//	Pipex
//	pipex
char	**line_filter(char **strs);
void	execute_cmd(t_shell *shell, char **argv, int child_id);
int		pipex(t_shell *shell, char **argv);
int		pipex_init(t_pipex *pipex, int argc, char **argv);
int		child_proc(t_shell *shell, char **argv, int child_id);
char	**list_convert(t_list *list);
//	pipex_utils
void	my_dup(t_pipex *pipex, int id, int mode);
void	execute_built_in(t_shell *shell, char **cmd, int lvl);
int		is_built_in(char *cmd);
int		create_pipes(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
int		prepare_strs(char **strs);
void	trim_strs(char **strs, const char *str);
void	cat_here_doc(t_pipex *pipex, char *limiter);
int		here_doc(t_pipex *pipex, char *limiter);
char	*get_next_line(int fd);
//	command
char	**get_cmd(t_pipex *pipex, char *str);
char	*path_checker(t_pipex *pipex, char *str);
int		check_built_in(t_shell *shell, char *str, int child_id);
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
int		ft_isalnum(int n);
int		ft_isalpha(int n);
int		ft_isdigit(int n);
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
int		ft_strlen_until(char *str, char *set);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_die(t_shell *shell, int todo, int code);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_countn(const char *str, const char c, int n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
t_env	*ft_search_in_list(t_list *list, char *name, int lvl);
void	*ft_realloc(void *p, size_t size, int dim, int new_dim);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
