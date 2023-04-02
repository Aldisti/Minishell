/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 08:36:28 by gpanico           #+#    #+#             */
/*   Updated: 2023/03/27 08:36:29 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_mat(void ***mat_addr)
{
	int	i;

	if (!(*mat_addr))
		return ;
	i = 0;
	while ((*mat_addr)[i])
	{
		ft_free(&(*mat_addr)[i]);
		i++;
	}
	ft_free((void **)mat_addr);
}