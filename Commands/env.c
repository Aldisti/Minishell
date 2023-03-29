/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afraccal <afraccal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:18:10 by afraccal          #+#    #+#             */
/*   Updated: 2023/03/27 11:12:30 by afraccal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(t_shell	*shell)
{
	while (shell->list)
	{
		printf("%s", shell->list->content->name);
		printf("%s\n", shell->list->content->value);
		shell->list=shell->list->next;
	}
}