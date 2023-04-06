/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:26:02 by gpanico           #+#    #+#             */
/*   Updated: 2023/03/28 14:15:54 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Descritpion: enanced free (see stdlib.h) in order to set at NULL the freed
 * 		pointer.
 * input:	the address of the pointer that will be freed casted as (void **).
 * Output:	na.
*/
void	ft_free(void **ptr_addr)
{
	if (!ptr_addr)
		return ;
	free(*ptr_addr);
	*ptr_addr = NULL;
}
