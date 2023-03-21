/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:34:49 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/20 12:49:53 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# define METACHR "\ \n\t|&()<>"
# include "libft/libft.h"
# include "get_next_line_bonus.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	char	**parsed;
	char	**token;
	char	*line;
	int		n_cmd;
	int		*n_pipe;
	int		infile;
	int		outfile;
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


#endif
