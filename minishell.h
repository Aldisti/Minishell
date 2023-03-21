/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:34:49 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/20 21:37:26 by marco            ###   ########.fr       */
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
# include "libft/libft.h"
# include "pipex/pipex.h"

typedef struct s_shell
{
	char	**parsed;
	char	*line;
	int		n_cmd;
	int		*n_pipe;
}	t_shell;

//	parser
char	**ft_parser(char *str);
//	executor
int		ft_executor(char **cmd);
//	Utils
char	*ft_strdup(const char *s1);
int		ft_isspace(int c);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
//Commands
char	*pwd(void);
void	print_pwd(void);
void	cd(char **argv, char **envp);


#endif
