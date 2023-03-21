/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:31:49 by mpaterno          #+#    #+#             */
/*   Updated: 2023/03/21 12:16:14 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include "../minishell.h"

typedef struct e_pipex{
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

char	**ft_parser(char *str);
void	free_cmd_n_file(t_pipex *pipex);
void	ft_free(char **strs);
void	child_free(t_pipex *pipex, char **cmd);
char	**path_n_command(t_pipex *pipex, char **argv, int el);
void	close_pipes(t_pipex *pipex);
char	**get_cmd(t_pipex *pipex, char **argv, int child_id);
void	r_trim(char **cmd1);
void	convert(char **strs);
void	protect_space(char *strs);
void	my_dup(int first, int second);
void	close_pipes(t_pipex *pipex);
int		create_pipes(t_pipex *pipex);
int		pipex(char **argv);

#endif