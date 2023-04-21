/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_star.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:04:23 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/21 12:20:25 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	ft_check_star(char *str)
{
	int	i;
	int	cont;
	int	quotes;

	i = -1;
	cont = 0;
	while (str[++i])
	{
		quotes = ft_getquotes(str, i);
		if (quotes)
			continue ;
		if (str[i] == 42 && !cont)
			cont++;
	}
	return (cont);
}

char	*ft_joiner_sep(char **strs, const char *sep)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	str = NULL;
	while (strs[++i])
	{
		tmp = ft_strjoin(str, strs[i]);
		ft_free((void **)&str);
		if (!tmp)
			return (0);
		if (strs[i + 1])
		{
			str = ft_strjoin(tmp, sep);
			ft_free((void **)&tmp);
			if (!str)
				return (0);
		}
		if (tmp)
			str = tmp;
	}
	tmp = ft_strtrim(str, " ");
	ft_free((void **)&str);
	return (tmp);
}

void	ft_check_exp(char **str, char **file)
{
	int	i;
	int	k;

	k = 0;
	i = -1;
	while ((*str)[++i])
	{
		while ((*str)[i] && (*str)[i] == 42 && (*str)[i + 1] == 42)
			i++;
		while ((*str)[i] == 42 && (*file)[k] && ((*file)[k] != (*str)[i + 1]
				|| ((*str)[i + 1] && (*file)[k + 1] != (*str)[i + 2]
					&& (*str)[i + 2] != 42)))
			k++;
		if ((*str)[i] == 42)
			i++;
		if ((*str)[i] != (*file)[k] || !(*file)[k])
			break ;
		k++;
	}
	if ((*str)[i] != (*file)[k])
		(*file) = ft_strdup("") + ft_free_a(&(*file), 0);
}

int	ft_do_exp_star(char **str)
{
	char	**fs;
	int		j;

	fs = ft_readdir_star(*str[0], ".");
	if (!fs)
		return (0);
	j = -1;
	while (fs[++j])
		ft_check_exp(str, &fs[j]);
	j = 0;
	while (fs[j] && !fs[j][0])
		j++;
	if (!fs[j])
	{
		ft_free_mat((void ***)&fs);
		return (1);
	}
	ft_free((void **)str);
	(*str) = ft_joiner_sep(fs, " ");
	ft_free_mat((void ***)&fs);
	return (1);
}

void	ft_exp_star(t_shell *sh)
{
	int	i;
	int	j;

	j = -1;
	sh->exp.strs[3] = 0;
	while (sh->parsed[++j])
	{
		if (!ft_check_star(sh->parsed[j]))
			continue ;
		sh->exp.pd = ft_parser(sh, sh->parsed[j], MC);
		if (!sh->exp.pd)
			ft_die(sh, 1, 12);
		i = -1;
		while (sh->exp.pd[++i])
		{
			if (!sh->exp.pd[i][0] || !ft_in(42, sh->exp.pd[i])
				|| ft_getquotes(sh->exp.pd[i], ft_strlen(sh->exp.pd[i]) - 1))
				continue ;
			if (!ft_do_exp_star(&(sh->exp.pd[i])))
				ft_die(sh, 1, 12);
		}
		ft_free((void **)&sh->parsed[j]);
		sh->parsed[j] = ft_joiner(sh->exp.pd, 0);
		ft_free_exp(&sh->exp);
	}
}
