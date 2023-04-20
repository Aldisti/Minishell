/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_until.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 08:27:15 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/20 14:29:05 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_until(char *str, char *set)
{
	int	i;

	i = 0;
	while (str[i] && !ft_in(str[i], set))
		i++;
	return (i);
}
