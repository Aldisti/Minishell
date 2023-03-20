/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:29:46 by gpanico           #+#    #+#             */
/*   Updated: 2023/03/20 08:38:17 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 10000

int		ft_fill(char **str, char **buffer, int fd);
int		ft_check_error(int r, char *str, char *buffer);
int		ft_buffer_al(int fd, char **buffer);
void	ft_free_buffer(int r, int fd, char **buffer);
char	*ft_strjoin(char *str, char *buffer, int step);
void	ft_movebuffer(char *buffer, int step);
char	*ft_realloc(char *str, char *buffer, int step);
char	*get_next_line(int fd);

#endif
