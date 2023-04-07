/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 08:36:28 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/07 09:27:29 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Description:	free an array of pointers and set NULL each pointer in the array
 * 		and the array pointer itself.
 * Input:	the array of pointer address casted as (void ***).
 * Output:	na.
*/
void	ft_free_mat(void ***mat_addr)
{
	int	i;

	i = 0;
	if (!mat_addr || !(*mat_addr))
		return ;
	while ((*mat_addr)[i])
	{
		ft_free(&(*mat_addr)[i]);
		i++;
	}
	ft_free((void **)mat_addr);
}
