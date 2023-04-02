#include "../minishell.h"

/*
#define OPEN_MODE  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
#define OPEN_FLAGS  O_CREAT | O_WRONLY | O_TRUNC

typedef struct s_elem
{
	char	**infiles;
	char	**outfiles;
	char	**afiles;
	int		*fdin;
	int		*fdout;
	int		*fda;
}	t_elem;
*/
void	ft_set_rarray(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->n_cmds)
	{
		shell->red.fdout[i] = 1;
		shell->red.fda[i] = 1;
		i++;
	}
}

int	ft_allocate_rarray(t_shell *shell)
{
	shell->red.infiles = (char **)ft_calloc(sizeof(char *),
				shell->n_cmds + 1);
	if (!shell->red.infiles)
		return (1); // ft_die(); Error: memory error
	shell->red.outfiles = (char **)ft_calloc(sizeof(char *),
				shell->n_cmds + 1);
	if (!shell->red.outfiles)
		return (1); // ft_die(); Error: memory error
	shell->red.afiles = (char **)ft_calloc(sizeof(char *),
				shell->n_cmds + 1);
	if (!shell->red.afiles)
		return (1); // ft_die(); Error: memory error
	shell->red.fdin = (int *)ft_calloc(sizeof(int), shell->n_cmds);
	if (!shell->red.fdin)
		return (1); // ft_die(); Error: memory error
	shell->red.fdout = (int *)ft_calloc(sizeof(int), shell->n_cmds);
	if (!shell->red.fdout)
		return (1); // ft_die(); Error: memory error
	shell->red.fda = (int *)ft_calloc(sizeof(int), shell->n_cmds);
	if (!shell->red.fda)
		return (1); // ft_die(); Error: memory error
	// inizializzo gli array di file descriptors
	ft_set_rarray(shell);
	return (0);
}

int	ft_valid_red_op(char *line)
{
	if (!ft_in(*(line + 1), "><"))
		return (1);
	else if (ft_in(*(line + 2), "><"))
		return (0);
	else if (*(line) == *(line + 1))
		return (1);
	else
		return (0);
}

int	ft_red_check(char *line)
{
	int	i;

	i = 0;
	// ciclo su tutta la stringa
	while (line[i])
	{
		// salto tutto quello presente tra apici
		ft_quotes_check(line, &i);
		if (ft_in(line[i], "><"))
		{
			// controllo se l'operatore e' valido
			if (!ft_valid_red_op(&line[i]))
				return (1); // Invalid operator
			// ciclo fino alla fine dell'operatore e controllo se dopo ci sono caratteri validi
			while (ft_in(line[i], ">< "))
				i++;
			if (!line[i] || ft_in(line[i], "><"))
				return (1); // Unexpected token
		}
		i++;
	}
}	

int	ft_check_space(char *line, int ind)
{
	if (line[ind] == ' ' && ft_in(line[ind + 1], "><"))
		return (1);
	return (0);
}

int	ft_get_fd(t_shell *shell, int n_cmd, int ind, char type)
{
	// controllo se l'operatore si trova all'inizio del comando
	// in tal caso ritorno il fd di default a seconda dell'operatore
	if (!ind)
	{
		// nel caso di < o << ritorno lo standard input
		if (ft_in(type, "ih"))
			return (0);
		// altrimenti per > e >> ritorno lo standard output
		else if (ft_in(type, "oa"))
			return (1);
	}
	// mi sposto sul carattere precedente l'operatore
	ind--;
	// ciclo fino ad arrivare all'inzio del comando 
	// o quando incontro un carattere diverso da un numero
	while (ind > 0 && ft_isdigit(shell->parsed[n_cmd][ind]))
		ind--;
	// controllo se il carattere sul quale m sono fermato e' uno spazio/numero
	// in caso negativo mando il fd di default
	if (!ft_in(shell->parsed[n_cmd][ind], " 0123456789")
		|| ft_check_space(shell->parsed[n_cmd], ind))
	{
		if (ft_in(type, "ih"))
			return (0);
		else if (ft_in(type, "oa"))
			return (1);
	}
	// altrimenti invio il fd specificato
	return (ft_atoi(&shell->parsed[n_cmd][ind]));
}

void	ft_put_filename(t_shell *shell, int n_cmd, char *dup, char type)
{
	if (type == 'a')
		shell->red.afiles[n_cmd / 2] = dup;
	else if (type == 'o')
		shell->red.outfiles[n_cmd / 2] = dup;
	else
		shell->red.infiles[n_cmd / 2] = dup;
}

int	ft_check_fn_status(t_shell *shell, int n_cmd, char type)
{
	if (type == 'o')
		if (!shell->red.outfiles[n_cmd / 2])
			return (1);
	else if (type == 'a')
		if (!shell->red.afiles[n_cmd / 2])
			return (1);
	else
		if (!shell->red.infiles[n_cmd / 2])
			return (1);
	return (0);
}

int	ft_get_filename(t_shell *shell, int n_cmd, int *ind, char type)
{
	int	i;
	char	tmp;
	
	// mi sposto sul primo carattere del filename
	while (shell->parsed[n_cmd][*ind] == ' ')
		(*ind)++;
	// utilizzo un secondo indice per conservare la posizione del primo carettere
	i = *ind;
	// ciclo fino ad arrivare alla fine del filename
	while (shell->parsed[n_cmd][i] && shell->parsed[n_cmd][i] != ' ')
	{
		// se nel filename sono presenti degli apici o doppi apici 
		// bisogna prendere tutto quello compreso tra essi
		if (ft_in(shell->parsed[n_cmd][i], "\'\""))
			ft_quotes_check(shell->parsed[n_cmd], &i);
		else
			i++;
	}
	// conservo il carattere dopo il filename
	// e lo rimpiazzo con un null byte per poter utilizzare la funzione str_dup
	tmp = shell->parsed[n_cmd][i];
	shell->parsed[n_cmd][i] = 0;
	ft_put_filename(shell, n_cmd, ft_strdup(&shell->parsed[n_cmd][*ind])
			, type);
	if (ft_check_fn_status(shell, n_cmd, type))
		return (1); // Error: memory error
	// sostituisco il null byte con il valore precedente
	shell->parsed[n_cmd][i] = tmp;
	// sposto l'indice che scorre il comandosull'ultimo carattere
	// del filename
	*ind = i - 1;
	return (0);
}

int	ft_strlen_without(char *str, char *set)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (!ft_in(str[i], set))
			len++;
		i++;
	}
	return (len);
}

int	ft_remove_quotes(char **line)
{
	char	*new_line;
	int	i;
	int	j;

	// se le lunghezze di line con e senza gli apici sono differenti
	// sostituisco la vecchia line con una nuova senza apici
	i = ft_strlen_without(*line, "\'\"");
	if ( i != ft_strlen(*line))
	{
		// alloco lo spazio di memoria necessario
		new_line = (char *)ft_calloc(sizeof(char), i + 1);
		if (!new_line)
			return (1); // Error: memory error
		i = 0;
		j = 0;
		// copio la vecchia line nella nuova facendo attenzione 
		// a non copiare anche gli apici
		while ((*line)[i])
		{
			if (!ft_in((*line)[i], "\'\""))
			{
				new_line[j] = (*line)[i];
				j++;
			}
			i++;
		}
		// libero la vecchia line e la rimpiazzo
		ft_free((void **) line);
		*line = new_line;
	}
	return (0);
}

int	ft_input_red(t_shell *shell, int n_cmd, int *ind)
{
	// controllo che l'operatore sia quello di input
	if (shell->parsed[n_cmd][*ind] == '<'
		&& !ft_in(shell->parsed[n_cmd][*ind + 1], "><"))
	{
		// salvo il fd nell'array utilizzando n_cmd / 2 
		// poiche' nella lista dei comandi sono presenti
		// anche le '|'
		shell->red.fdin[n_cmd / 2] = ft_get_fd(shell, n_cmd,
				*ind, 'i');
		// mi muovo alla fine dell'operatore
		while (ft_in(shell->parsed[n_cmd][*ind], "><"))
			(*ind)++;
		// salvo il filename nella shell
		if (ft_get_filename(shell, n_cmd, ind, 'i'))
			return (1); // Error: memory error
		// rimuovo gli apici dal filename
		if (ft_remove_quotes(&shell->red.infiles[n_cmd / 2]))
			return (1); // Error: memory error
		// controllo se esiste il file e se si hanno i permessi per leggerlo
		if (access(shell->red.infiles[n_cmd / 2], F_OK | R_OK))
			return (2); // file doesn't exist
	}
	return (0);
}

int	ft_output_red(t_shell *shell, int n_cmd, int *ind)
{
	int fd;

	// controllo che l'operatore sia quello di output
	if (shell->parsed[n_cmd][*ind] == '>'
		&& !ft_in(shell->parsed[n_cmd][*ind + 1], "><"))
	{
		// salvo il fd nell'array utilizzando n_cmd / 2
		// poiche' nella lista dei comandi sono presenti
		// anche le '|'
		shell->red.fdout[n_cmd / 2] = ft_get_fd(shell, n_cmd,
				*ind, 'o');
		// mi muovo alla fine dell'operatore
		while (ft_in(shell->parsed[n_cmd][*ind], "><"))
			(*ind)++;
		// salvo il filename nella shell
		if (ft_get_filename(shell, n_cmd, ind, 'o'))
			return (1); // Error: memory error
		// rimuovo gli apici dal filename
		if (ft_remove_quotes(&shell->red.outfiles[n_cmd / 2]))
			return (1); // Error: memory error
		// se esiste elimino il filename presente in afile
		ft_free((void **) shell->red.afiles[n_cmd / 2]);
		// creo il file
		fd = open(shell->red.outfiles[n_cmd / 2], OPEN_FLAGS, OPEN_MODE);
		if (fd == -1)
			return (1); // Error: memory error
		close(fd);
	}
	return (0);
}

int	ft_append_red(t_shell *shell, int n_cmd, int *ind)
{
	int fd;

	// controllo che l'operatore sia quello di append
	if (shell->parsed[n_cmd][*ind] == '>'
		&& shell->parsed[n_cmd][*ind + 1] == '>')
	{
		// salvo il fd nell'array utilizzando n_cmd / 2
		// poiche' nella lista dei comandi sono presenti
		// anche le '|'
		shell->red.fda[n_cmd / 2] = ft_get_fd(shell, n_cmd,
				*ind, 'a');
		// mi muovo alla fine dell'operatore
		while (ft_in(shell->parsed[n_cmd][*ind], "><"))
			(*ind)++;
		// salvo il filename nella shell
		if (ft_get_filename(shell, n_cmd, ind, 'a'))
			return (1); // Error: memory error
		// rimuovo gli apici dal filename
		if (ft_remove_quotes(&shell->red.afiles[n_cmd / 2]))
			return (1); // Error: memory error
		// se esiste elimino il filename presente in outfile
		ft_free((void **) shell->red.outfiles[n_cmd / 2]);
		// creo il file
		fd = open(shell->red.afiles[n_cmd / 2], O_CREAT | O_WRONLY,
				OPEN_MODE);
		if (fd == -1)
			return (1); // Error: memory error
		close(fd);
	}
	return (0);
}

int	ft_here_doc(char *limiter)
{
	char	*temp;
	int		file;

	file = open(".here_doc", OPEN_FLAGS , OPEN_MODE);
	if (file == -1)
		return (1); // Error: memory error
	while (42)
	{
		write(1, "heredoc> ", 9);
		temp = get_next_line(0);
		if (!temp || (!ft_strncmp(temp, limiter, ft_strlen(limiter))
				&& ft_strlen(temp) == ft_strlen(limiter) + 1))
			break ;
		write(file, temp, ft_strlen(temp));
		free(temp);
	}
	close(file);
	if (temp)
		free(temp);
	return (0);
}

int	ft_hdoc_red(t_shell *shell, int n_cmd, int *ind)
{
	// controllo che l'operatore sia quello di here document
	if (shell->parsed[n_cmd][*ind] == '<'
		&& shell->parsed[n_cmd][*ind + 1] == '<')
	{
		// salvo il fd nell'array utilizzando n_cmd / 2 
		// poiche' nella lista dei comandi sono presenti
		// anche le '|'
		shell->red.fdin[n_cmd / 2] = ft_get_fd(shell, n_cmd,
				*ind, 'h');
		// mi muovo alla fine dell'operatore
		while (ft_in(shell->parsed[n_cmd][*ind], "><"))
			(*ind)++;
		// salvo momentaneamente nella shell il terminatore
		if (ft_get_filename(shell, n_cmd, ind, 'h'))
			return (1); // Error: memory error
		// rimuovo gli apici dal terminatore
		if (ft_remove_quotes(&shell->red.infiles[n_cmd / 2]))
			return (1); // Error: memory error
		// creo il file temporaneo here_doc
		if (ft_here_doc(shell->red.infiles[n_cmd / 2]))
			return (1); // Error: memory error
		// sostituisco il terminatore con '.here_doc' e libero il terminatore
		ft_free((void **) &shell->red.infiles[n_cmd / 2]);
		shell->red.infiles[n_cmd / 2] = ft_strdup(".here_doc");
		if (!shell->red.infiles[n_cmd / 2])
			return (1); // Error: memory error
	}
	return (0);
}

int	ft_apply_red(t_shell *shell, int n_cmd)
{
	int	i;
	int	ret;
	
	i = 0;
	// ciclo sul comando
	while (shell->parsed[n_cmd][i])
	{
		// salto tutto quello presente tra apici
		ft_quotes_check(shell->parsed[n_cmd], &i);
		// controllo se il carattere sul quale mi trovo e' un operatore di redirezionamento
		if (ft_in(shell->parsed[n_cmd][i], "><"))
		{
			// in caso affermativo salvo il fd e il filename
			ret = ft_input_red(shell, n_cmd, &i);
			if (ret == 1)
				return (1); // Error: memory error
			else if (ret == 2)
				return (2); // Error: cannot read file
			else if (ft_output_red(shell, n_cmd, &i))
				return (1); // Error: memory error
			else if (ft_append_red(shell, n_cmd, &i))
				return (1); // Error: memory error
			else if (ft_hdoc_red(shell, n_cmd, &i))
				return (1); // Error: memory error
		}
		i++;
	}
	return (0);
}

void	ft_replace_op(char *cmd, int *ind)
{
	// sostituisco il primo carattere dell'operatore
	cmd[*ind] = '\31';
	// controllo se l'operatore e' da due caratteri e 
	// in tal caso sostituisco anche il secondo
	if (ft_in(cmd[*ind + 1], "><"))
	{
		(*ind)++;
		cmd[*ind] = '\31';
	}
	// mi sopsto al carattere successivo
	(*ind)++;
}

void	ft_replace_fd(char *cmd, int ind)
{
	// controllo se l'operatore si trova all'inizio del comando
	// in tal caso esco dalla funzione
	if (!ind)
		return ;
	// mi sposto sul carattere precedente l'operatore
	ind--;
	// ciclo fino ad arrivare all'inzio del comando 
	// o quando incontro un carattere diverso da un numero
	while (ind > 0 && ft_isdigit(cmd[ind]))
		ind--;
	// controllo se il carattere sul quale mi sono fermato e' uno spazio/numero
	// in caso affermativo sostituisco il fd facendo attenzione a non sostituire
	// lo spazio prima di esso
	if (ft_in(cmd[ind], " 0123456789"))
	{
		if (cmd[ind] == ' ')
			ind++;
		while (!ft_in(cmd[ind], "><"))
		{
			cmd[ind] = '\31';
			ind++;
		}
	}
}

void	ft_quotes_replace(char *str, int *ind, char sub)
{
	if (str[*ind] == '\'')
	{
		str[*ind] = sub;
		(*ind)++;
		while (str[*ind] != '\'')
		{
			str[*ind] = sub;
			(*ind)++;
		}
	}
	else if (str[*ind] == '\"')
	{
		str[*ind] = sub;
		(*ind)++;
		while (str[*ind] != '\"')
		{
			str[*ind] = sub;
			(*ind)++;
		}
	}
}

void	ft_replace_fn(char *cmd, int *ind)
{
	// mi sposto sul primo carattere del filename sostituendo tutti gli spazi
	// con '\31'
	while (cmd[*ind] == ' ')
	{
		cmd[*ind] = '\31';
		(*ind)++;
	}
	// ciclo fino ad arrivare alla fine del filename e lo sostituisco
	while (cmd[*ind] && cmd[*ind] != ' ')
	{
		// sostituisco tutto quello presente tra apici o doppi apici
		ft_quotes_replace(cmd, ind, '\31');
		cmd[*ind] = '\31';
		(*ind)++;
	}
	(*ind)--;
}

void	ft_replace_red(t_shell *shell,int n_cmd)
{
	int	i;
	
	i = 0;
	// ciclo sul comando
	while (shell->parsed[n_cmd][i])
	{
		// salto tutto quello presente tra apici
		ft_quotes_check(shell->parsed[n_cmd], &i);
		// controllo se il carattere sul quale mi trovo e' un operatore di redirezionamento
		if (ft_in(shell->parsed[n_cmd][i], "><"))
		{
			// in caso affermativo sostituisco il fd, l'operatore e il filename
			ft_replace_fd(shell->parsed[n_cmd], i);
			ft_replace_op(shell->parsed[n_cmd], &i);
			ft_replace_fn(shell->parsed[n_cmd], &i);
		}
		i++;
	}
}

char	*ft_null_to_str(char *ptr)
{
	if (!ptr)
		ptr = ft_strdup("");
	return (ptr);
}

int	ft_fill_red(t_shell *shell)
{
	int	i;

	// ciclo tutti i filename
	i = 0;
	while (i < shell->n_cmds)
	{
		// se il filename non esiste gli associo una stringa vuota
		shell->red.infiles[i] = ft_null_to_str(shell->red.infiles[i]);
		if (!shell->red.infiles[i])
			return (1); // Error: memory error
		shell->red.outfiles[i] = ft_null_to_str(shell->red.outfiles[i]);
		if (!shell->red.infiles[i])
			return (1); // Error: memory error
		shell->red.afiles[i] = ft_null_to_str(shell->red.afiles[i]);
		if (!shell->red.infiles[i])
			return (1); // Error: memory error
		i++;
	}
	return (0);
}

void	ft_redirection(t_shell *shell)
{
	int	i;
	int	ret;

	// alloco lo spazio di memoria necessario per i sei array della redirection
	if (ft_allocate_rarray(shell))
		exit(1); // ft_die(); Error: memory error
	// ciclo tutti i comandi
	i = 0;
	while (shell->parsed[i])
	{
		// controllo se nel comando si trovano redirection non valide
		if (ft_red_check(shell->parsed[i]))
			exit(4); // ft_die(); Error: unexpected token/invalid operator
		// passo al comando successivo
		i++;
	}
	// ciclo di nuovo per salvare le redirection e creare eventuali file
	i = 0;
	while (shell->parsed[i])
	{
		// salvo negli array tutte le redirection per l'iesimo comando
		ret = ft_apply_red(shell, i);
		if (ret == 1)
			exit(1); // ft_die(); Error: memory error
		// se viene trovato un errore di lettura si passa al comando successivo
		else if (ret == 2 && ++i)
			continue;
		// scambio tutte le redirection con '\31'
		ft_replace_red(shell, i);
		// passo al comando successivo
		i++;
	}
	// sostituisco tutti i null pointer con stringhe vuote
	if (ft_fill_red(shell))
		exit(1); // ft_die(); Error: memory error
}
