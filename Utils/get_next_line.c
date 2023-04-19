/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:17:14 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/18 21:45:25 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*print_remain(char	*str)
{
	char	*ret;
	char	*new_buff;
	int		i;

	new_buff = ft_strchr(str, '\n') + 1;
	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	ret = (char *) malloc((i + 2) * sizeof(char));
	ft_strlcpy(ret, str, i + 2);
	if (ft_strchr(str, '\n'))
		ft_strlcpy(str, new_buff, ft_strlen(new_buff) + 1);
	else
	{
		i = -1;
		while (++i < 10)
			str[i] = 0;
	}
	return (ret);
}

char	*get_line(int fd)
{
	char	buff[10 + 1];
	int		flag;
	char	*ret;
	int		i;

	flag = 1;
	ret = ft_strdup("");
	buff[10] = 0;
	while (ft_strchr(ret, '\n') == 0 && flag)
	{
		i = -1;
		while (++i < 10)
			buff[i] = 0;
		flag = read(fd, buff, 10);
		ret = gnl_join(ret, buff);
		if (flag <= 0 && !*ret)
		{
			free(ret);
			return (0);
		}
	}
	return (ret);
}

char	**parser(char *str, int len0)
{
	char	**ret;
	int		len1;
	char	*chr;

	if (!str)
		return (0);
	chr = ft_strchr(str, '\n');
	len0 = 0;
	while (str[len0] && str[len0] != '\n')
		len0++;
	len0++;
	if (chr != 0)
		len0 = ((chr + 1) - str) + 1;
	if (chr == 0)
		len1 = 0;
	else
		len1 = ft_strlen(chr + 1) + 1;
	ret = (char **) malloc(2 * sizeof(char *));
	ret[0] = (char *)malloc((len0) * sizeof(char));
	ret[1] = (char *)malloc((len1) * sizeof(char));
	ft_strlcpy(ret[0], str, len0);
	if (len1 > 0)
		ft_strlcpy(ret[1], (chr + 1), len1);
	free(str);
	return (ret);
}

void	free_all(char **strs, char *str, char *buff)
{
	ft_strlcpy(buff, strs[1], ft_strlen(strs[1]) + 1);
	free(strs[0]);
	free(strs[1]);
	free(strs);
	free(str);
}

char	*get_next_line(int fd)
{
	static char	buff[10 + 1];
	char		*full;
	char		*str;
	char		**strs;
	char		*ret;

	if (fd < 0 || 10 <= 0)
		return (NULL);
	if (ft_strchr(buff, '\n'))
		return (print_remain(buff));
	str = get_line(fd);
	if (!str)
	{
		if (buff[0])
			return (print_remain(buff));
		return (0);
	}
	if (ft_strchr(str, '\n') == 0 && !buff[0])
		return (str);
	full = ft_strdup(buff);
	full = gnl_join(full, str);
	strs = parser(full, 0);
	ret = ft_strdup(strs[0]);
	free_all(strs, str, buff);
	return (ret);
}
