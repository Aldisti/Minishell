#include "../minishell.h"

void	ft_clear_levels(t_shell	*shell, int lvl)
{
	t_env	*tmp_elem;
	t_env	*previous;
	t_list	*previous_node;
	t_list	*tmp_node;

	// primo nodo della lista
	if (shell->list->content)
	{
		tmp_elem = (t_env *) shell->list->content;
		// se il primo elemento di content ha un livello uguale
		// o superiore a quello richiestodeve essere elminato 
		// tutto il nodo
		if (tmp_elem->level >= lvl)
		{
			while (tmp_elem)
			{
				previous = tmp_elem;
				tmp_elem = tmp_elem->next;
				ft_free((void **) &previous->name);
				ft_free((void **) &previous->value);
				ft_free((void **) &previous);
			}
			tmp_node = shell->list;
			shell->list = shell->list->next;
			ft_free((void **) &tmp_node);
		}
		// altrimenti solo quelli elementi che hanno livello superiore
		// vanno eliminati
		else
		{
			while (tmp_elem->next && tmp_elem->next->level < lvl)
				tmp_elem = tmp_elem->next;
			if (tmp_elem->next)
			{
				previous = tmp_elem;
				tmp_elem = tmp_elem->next;
				previous->next = NULL;
				while (tmp_elem)
				{
					previous = tmp_elem;
					tmp_elem = tmp_elem->next;
					ft_free((void **) &previous->name);
					ft_free((void **) &previous->value);
					ft_free((void **) &previous);
				}
			}
		}
	}
	// elementi centrali della lista
	previous_node = shell->list;
	tmp_node = shell->list->next;
	while (tmp_node && tmp_node->content)
	{
		tmp_elem = (t_env *) tmp_node->content;
		// se il primo elemento di content ha un livello uguale
		// o superiore a quello richiestodeve essere elminato 
		// tutto il nodo
		if (tmp_elem->level >= lvl)
		{
			while (tmp_elem)
			{
				previous = tmp_elem;
				tmp_elem = tmp_elem->next;
				ft_free((void **) &previous->name);
				ft_free((void **) &previous->value);
				ft_free((void **) &previous);
			}
			previous_node->next = tmp_node->next;
			ft_free((void **) &tmp_node);
			tmp_node = previous_node->next;
		}
		// altrimenti solo quelli elementi che hanno livello superiore
		// vanno eliminati
		else
		{
			while (tmp_elem->next && tmp_elem->next->level < lvl)
				tmp_elem = tmp_elem->next;
			if (tmp_elem->next)
			{
				previous = tmp_elem;
				tmp_elem = tmp_elem->next;
				previous->next = NULL;
				while (tmp_elem)
				{
					previous = tmp_elem;
					tmp_elem = tmp_elem->next;
					ft_free((void **) &previous->name);
					ft_free((void **) &previous->value);
					ft_free((void **) &previous);
				}
			}
			previous_node = tmp_node;
			tmp_node = tmp_node->next;
		}
	}
}
