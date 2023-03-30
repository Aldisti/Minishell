#include "../minishell.h"

int	ft_count_cmds(char *line)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	// ciclo su tutta la stringa
	while (line[i])
	{
		// salto tutto quello che si trova tra apici
		ft_quotes_check(line, &i);
		// se incontro un operatore aggiorno il counter e mi muovo
		// alla fine di quello
		if (ft_in(line[i], "|&"))
		{
			n++;
			while (ft_in(line[i + 1], "|&"))
				i++;
		}
		// muovo la stringa al prossimo carattere
		i++;
	}
	return (n);
}

int	ft_update_lvl(char c, int lvl, int *array)
{
	// se il carattere e' una parentesi aperta ritorno il livello incrementato di uno	
	if (c == '(')
		return (lvl + 1);
	// se invece e' una parentesi chiusa salvo il livello, se non era stato fatto in precedenza
	// e successivamente ritorno il livello decremantato
	else if (c == ')')
	{
		if (!array[0])
			array[0] = lvl;
		return (lvl - 1);
	}
	// in tutti gli altri casi torno il livello invariato
	return (lvl);
}

void	ft_set_lvls(char *line, int *lvls)
{
	int	i;
	int	j;
	int	lvl;

	i = 0;
	j = 0;
	lvl = 0;
	// ciclo su tutta la stringa
	while (line[i])
	{
		// salto tutto quello che si trova tra apici
		ft_quotes_check(line, &i);
		// aggiorno il livello 
		lvl = ft_update_lvl(line[i], lvl, &lvls[j]);
		// se arrivo alla fine di un comando e il livello non era stato salvato lo salvo,
		// atrimenti mi sposto al comando successivo
		if (ft_in(line[i], "|&"))
		{
			while (ft_in(line[i + 1], "|&"))
				i++;
			if (!lvls[j])
				lvls[j] = lvl;
			j++;
		}
		// muovo la stringa al prossimo carattere
		i++;
	}
}

void	ft_replace(char *line, char *old, char new)
{
	int	i;

	i = 0;
	// ciclo su tutta la stringa
	while (line[i])
	{
		// salto tutto quello presente tra apici
		ft_quotes_check(line, &i);
		// se il carattere e' tra quelli in 'old' lo sostituisco con 'new'
		if (ft_in(line[i], old))
			line[i] = new;
		// muovo la stringa al carattere successivo
		i++;
	}
}

int	ft_lvls(t_shell *shell)
{
	char	*line;

	// tmp
	shell->lvls = NULL;
	ft_free((void **) &shell->lvls);
	// tmp
	// unisco l'input diviso in precedenza per poter eliminare le parentesi correttamente
	line = ft_joiner(shell->parsed, 0);
	if (!line)
		return (1); // ft_die(); Error: memory error
	// libero il vecchio input per evitare leaks
	ft_free_mat((void ***) &shell->parsed);
	// conto il numero di comandi presenti nell'input
	shell->n_cmds = ft_count_cmds(line);
	// alloco in memoria spazio necessario per conservare il livello di ogni comando
	shell->lvls = (int *)ft_calloc(sizeof(int), shell->n_cmds);
	if (!shell->lvls)
		return (1); // ft_die(); Error: memory error
	// determino il livello di ogni comando e lo conservo in shell->lvls
	ft_set_lvls(line, shell->lvls);
	// rimuovo tutte le parentesi presenti nell'input
	ft_replace(line, "()", ' ');
	// associo a shell->parsed la nuova versione dell'input divisa per operatori e senza parentesi
	shell->parsed = ft_parser(shell, line, "|&");
	if (!shell->parsed)
		return (1); // ft_die(); Error: memory error
	// infine libero lo spazio di memoria associato a line
	ft_free((void **) &line);
	return (0);
}
