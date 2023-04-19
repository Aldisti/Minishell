/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:03:52 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/19 09:50:32 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

long	ft_free_a(char **elem, long n)
{
	if (*elem)
		ft_free((void **)elem);
	elem = 0;
	return (n);
}

void	*ft_free_exp(t_exp *exp)
{
	if (exp->pd)
		ft_free_mat((void ***)&exp->pd);
	if (exp->sp)
		ft_free_mat((void ***)&exp->sp);
	if (exp->tmp)
		ft_free_mat((void ***)&exp->tmp);
	return (NULL);
}

void	*ft_free_mat_a(void ***elem, int size)
{
	int	i;

	if (size == -1)
		while ((char **)(*elem)[++size])
			;
	i = -1;
	while (++i < size)
		ft_free((void **)&(*elem)[i]);
	(*elem) = 0;
	return (0);
}

char	*ft_put_quotes(t_shell *shell, char *origin)
{
	int		i;

	shell->exp.pd = ft_parser(shell, origin, ">|<");
	if (!shell->exp.pd)
		ft_die(shell, 1, 12);
	i = -1;
	shell->exp.strs[3] = (char *) ft_free_a(&origin, 0);
	while (shell->exp.pd[++i])
	{
		if (ft_in(shell->exp.pd[i][0], ">|<"))
		{
			shell->exp.strs[0] = "\"";
			shell->exp.strs[2] = "\"";
			shell->exp.strs[1] = shell->exp.pd[i];
			shell->exp.pd[i] = ft_joiner(shell->exp.strs, 0);
			if (!shell->exp.pd[i])
				ft_die(shell, 1, 12);
			ft_free((void **)&shell->exp.strs[1]);
		}
	}
	origin = ft_joiner(shell->exp.pd, 1);
	if (!origin)
		ft_die(shell, 1, 12);
	return (origin);
}

int	ft_check_for_op(t_exp *exp, char *str)
{
	int		i;
	int		j;

	j = ft_find_in_array(exp->sp, str);
	if (j-- <= 0)
		return (0);
	i = ft_strlen(exp->sp[j]) - 1;
	while (i >= 0 && ft_isspace(exp->sp[j][i]))
		i--;
	if (ft_in(exp->sp[j][i], "><") && i == 0)
		return (1);
	if (ft_in(exp->sp[j][i], "><") && i > 0 && exp->sp[j][i - 1] == '<')
		return (2);
	else if (ft_in(exp->sp[j][i], "><") && i > 0 && exp->sp[j][i - 1] != '<')
		return (1);
	return (0);
}
