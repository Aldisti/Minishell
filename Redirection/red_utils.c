#include "../minishell.h"

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

char	*ft_null_to_str(char *ptr)
{
	if (!ptr)
		ptr = ft_strdup("");
	return (ptr);
}

int	ft_fill_red(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->n_cmds)
	{
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
