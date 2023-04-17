/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:34:49 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/17 11:57:15 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <dirent.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

# ifndef MC
#  define MC " \n\t|&<>()"
# endif
# ifndef MSG_ERR
#  define MSG_ERR "\033[31mBad Syntax: error near unexpected operator\033[0m\n"
# endif

extern void	rl_replace_line(char *text, int clear_undo);
extern void	rl_clear_history(void);

typedef struct s_red
{
	char	**infiles;
	char	**outfiles;
	char	**afiles;
	int		*fdin;
	int		*fdout;
	int		*fda;
}	t_red;

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
	int		original_stdin;
	pid_t	*pid;
	int		cmd_i;
	char	**paths;
}	t_pipex;

typedef struct s_shell
{
	struct sigaction	a_nothing;
	struct sigaction	a_int;
	struct sigaction	a_quit;
	struct termios		tty_attrs;
	char				**parsed;
	char				**envp;
	char				**files;
	char				*line;
	int					*fd_input;
	int					*fd_output;
	int					*lvls;
	int					n_cmds;
	t_red				red;
	t_list				*list;
	t_pipex				pipex;
}	t_shell;

void		my_print(char **strs);
//	Init
//	shell_set
void		ft_shell_set(t_shell *shell);
//	env_set
t_list		*ft_env_set(char **envp);
char		*ft_get_name(const char *str);
char		*ft_get_value(const char *str, const char *name, int n);
void		ft_die_env(t_list *list, t_list *list_elem, t_env *elem);
//	signals_set
void		ft_handle_int(int signum);
void		ft_handle_quit(int signum);
void		ft_does_nothing(int signum);
void		ft_signals_set(t_shell *shell);

//	Readline
//	readline
char		*ft_readline(char *prompt);
char		*ft_read_again(char *prompt);
int			ft_end_with(char *line, char end);
void		*ft_die_readline(char **lines, int dim);

//	Readline
//	readline
char		*ft_readline(char *prompt);
char		*ft_read_again(char *prompt);
int			ft_end_with(char *line, char end);
void		*ft_die_readline(char **lines, int dim);

//	Parser
//	parser
int			ft_in(char c, char *set);
int			ft_checks(char *line, int *i);
int			ft_quotes_check(char *line, int *i);
int			ft_parenthesis_check(char *line, int *i);
char		**ft_extract_word(char **parsed, int *dim, int *i, char **line);
//	parser2
int			ft_check_multi_par(char *line);
int			ft_valid_operators(char **parsed);
char		**ft_parser_checks(t_shell *shell);
char		**ft_parser(t_shell *shell, char *line, char *set);
//	parser3
int			ft_check_beforepar(char *line);
int			ft_valid_command(char **parsed);
void		*ft_die_parser(t_shell *shell, char **parsed);

//	Expansions
//	expansion
char		*ft_expand_spec(char *str);
void		ft_expand_all(t_shell *shell, char **parsed);
char		*ft_exp_tilde(t_shell *shell, char *str, int lvl);
char		*ft_expand_doll(t_shell *shell, char *str, int lvl);
char		**ft_split_expansions(t_shell *shell, char *str, int j, int k);
//	expansion_utils
int			ft_getlvl(char *str, int i);
int			ft_free_a(char **elem, int n);
char		*ft_getname(char *str, int i);
int			ft_getquotes(char *str, int i);
void		*ft_free_mat_a(void ***elem, int size);

//	Parentheses
//	parentheses
int			ft_lvls(t_shell *shell);
int			ft_counts_cmds(char *line);
void		ft_set_lvls(char *line, int *lvls);
int			ft_update_lvl(char c, int lvl, int *array);
void		ft_replace(char *line, char *old, char new);

//	Redirection
void		last_cmd_dup(t_shell *shell, int id);
void		alone_cmd_dup(t_shell *shell, int id);
void		middle_cmd_dup(t_shell *shell, int id);
void		first_child_dup(t_shell *shell, int id);
void		red_selector(t_shell *shell, int id, int mode);
//	red
int			ft_redirection(t_shell *shell);
//	red_check
int			ft_red_check(t_shell *shell, char *line);
int			ft_valid_red_op(char *line);
int			ft_check_space(char *line, int ind);
int			ft_check_fn_status(t_shell *shell, int n_cmd, char type);
//	red_init
void		ft_set_rarray(t_shell *shell);
void		ft_allocate_rarray(t_shell *shell);
//	red_operators
int			ft_hdoc_red(t_shell *shell, int n_cmd, int *ind);
int			ft_input_red(t_shell *shell, int n_cmd, int *ind);
int			ft_output_red(t_shell *shell, int n_cmd, int *ind);
int			ft_append_red(t_shell *shell, int n_cmd, int *ind);
int			ft_here_doc(t_shell *shell, char *limiter);
int			ft_hdoc_red(t_shell *shell, int n_cmd, int *ind);
//	red_parse
int			ft_get_fd(t_shell *shell, int n_cmd, int ind, char type);
void		ft_put_filename(t_shell *shell, int n_cmd, char *dup, char type);
int			ft_get_filename(t_shell *shell, int n_cmd, int *ind, char type);
int			ft_remove_quotes(t_shell *shell, char **line);
int			ft_apply_red(t_shell *shell, int n_cmd);
int			ft_get_fd(t_shell *shell, int n_cmd, int ind, char type);
int			ft_get_filename(t_shell *shell, int n_cmd, int *ind, char type);
void		ft_put_filename(t_shell *shell, int n_cmd, char *dup, char type);
//	red_replace
void		ft_replace_fd(char *cmd, int ind);
void		ft_replace_fn(char *cmd, int *ind);
void		ft_replace_op(char *cmd, int *ind);
void		ft_replace_red(t_shell *shell, int n_cmd);
void		ft_quotes_replace(char *str, int *ind, char sub);
//	red_utils
char		*ft_null_to_str(char *ptr);
int			ft_fill_red(t_shell *shell);
int			ft_strlen_without(char *str, char *set);
int			ft_intab(char *str, char **tab);

//	Commands
//	cd
int			get_oldpwd_i(char **envp);
int			cd(t_shell *shell, char **cmd, int lvl);
int			args_count(char **argv);
void		update_oldpwd(t_shell *shell, char *str, int lvl);
//	pwd
int			print_pwd(t_shell *shell);
// exit
int			ft_exit(t_shell *shell, char **strs, char **cmd);
//	env
int			env(t_shell	*shell, int lvl);
//	echo
void		print_cmd(char *cmd);
int			echo(char **argv);
//	export
int			ft_print_export(t_shell *shell, int lvl);
int			ft_export(t_shell *shell, char **cmd, int lvl);
//	export_utils
void		ft_print_env(t_list *lst);
t_env		*ft_env_new(char *name, char *value, int lvl);
void		ft_do_export2(t_list *list, t_env **new_env, int lvl);
void		ft_do_export1(t_shell *shell, t_env **new_env,
				char *name, int lvl);
void		ft_set_name_value(t_shell *shell, char **name,
				char **value, char *cmd);
//	unset
void		ft_clean_list(t_shell *shell);
int			ft_unset(t_shell *shell, char **cmd, int lvl);

//	Pipex
//	pipex
char		**line_filter(char **strs);
int			pipex(t_shell *shell, char **argv);
int			pipex_init(t_pipex *pipex, int argc);
int			child_proc(t_shell *shell, char **argv, int *child_id);
void		execute_cmd(t_shell *shell, char **argv, int *child_id);
char		*gnp(t_shell *shell, char *str);
//	pipex_utils
int			is_blt(char *cmd);
char		*get_next_line(int fd);
int			prepare_strs(t_shell *shell, char **strs);
int			pipes(t_pipex *pipex, const char *mode);
void		my_dup(t_shell *shell, int id);
void		red_output(t_shell *shell, int id);
void		trim_strs(t_shell *shell, char **strs, const char *str);
void		execute_built_in(t_shell *shell, char **strs, int lvl, int id);
//	pipex_utils2
char		**ft_take_paths(t_shell *shell, int id);
void		ft_exit_exec(t_shell *shell, char **argv, char **cmd, int type);
//	command
char		**get_cmd(t_shell *shell, char *str, int id);
char		*path_checker(t_pipex *pipex, char **str, int i);
int			built_in_selector(t_shell *shell, int *id, char **cmd);
void		get_cmd_loop(t_shell *shell, char *temp, char **command);
void		built_in_pipe_handler(t_shell *shell, int *id, char **cmd);
//	command_parser
char		**command_parser(char *str, char *set);
int			ft_quotes_check_command(char *line, int	*i);
char		**ft_extract_word_command(char **parsed, int *dim,
				int *i, char **line);
//	free
void		child_free(t_pipex *pipex, char **cmd);

//	Utils
//	is
int			ft_isalnum(int n);
int			ft_isalpha(int n);
int			ft_isdigit(int n);
int			ft_isspace(int c);
//	free
void		ft_free(void **strs);
int			ft_free_env(t_env **env);
void		ft_free_list(t_list **list);
void		ft_free_mat(void ***mat_addr);
void		ft_free_shell(t_shell *shell);
void		ft_free_routine(t_shell *shell);
void		ft_clean_level(t_shell *shell, int lvl);
void		ft_clean_from_lvl(t_shell *shell, int lvl);
int			ft_die(t_shell *shell, int todo, int code);
//	str
char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *str);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *str, int c);
int			ft_strlen_until(char *str, char *set);
void		*ft_memset(void *b, int c, size_t len);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
//	lst
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(void *content);
t_env		*ft_get_env(t_list	*list, int lvl);
char		**list_convert(t_list *list, int lvl);
t_env		*ft_envfind_sort(t_env *env, int lvl);
void		ft_env_insert(t_env **env, t_env *new);
void		ft_envadd_front(t_env **env, t_env *new);
void		ft_lst_insert(t_list **lst, t_list *new);
void		ft_clear_levels(t_shell	*shell, int lvl);
t_list		*ft_lstfind_sort(t_list *lst, char *name);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
t_list		*ft_get_node(t_list *list, const char *name);
t_env		*ft_search_in_list(t_list *list, char *name, int lvl);
//	other
char		*ft_itoa(int n);
int			ft_atoi(const char *str);
int			ft_atoi_zero(const char *str);
char		*ft_joiner(char **tab, int n);
char		**ft_split(char const *s, char c);
void		*ft_calloc(size_t num, size_t dim);
int			ft_countn(const char *str, const char c, int n);
void		*ft_realloc(void *p, size_t size, int dim, int new_dim);
char		**ft_readdir(char *path);
int			fd_printf(int fd, const char *str, ...);
void		check_execute(t_shell *shell, char *str, int *id);

#endif
