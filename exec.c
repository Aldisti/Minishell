#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*ptr;

	if (!s)
		return (0);
	if (start >= strlen(s))
		return (0);
	if (len > strlen(s))
		len = strlen(s);
	ptr = (char *) malloc ((len + 1) * sizeof (char));
	if (!ptr)
		return (0);
	i = 0;
	while (len-- > 0 && s[start])
		ptr[i++] = s[start++];
	ptr[i] = 0;
	return (ptr);
}

int	ft_strnbr(char const *str, char chr)
{
	int		c;

	while (*str && *str == chr)
		str++;
	c = 0;
	while (*str)
	{
		if (*str == chr)
		{
			while (*str == chr && *str)
				str++;
			c++;
		}
		else
			str++;
	}
	if (*(--str) == chr && c)
		c--;
	return (c);
}

char	**ft_fill(char const *s, char c)
{
	char	**ptr;
	int		j;
	int		k;

	ptr = (char **) calloc((ft_strnbr(s, c) + 2), sizeof (char *));
	if (!ptr)
		return (0);
	k = 0;
	while (*s)
	{
		if (*s != c)
		{
			j = 0;
			while (*s && *s != c && ++j)
				s++;
			ptr[k++] = ft_substr(s - j, 0, j);
		}
		else
			s++;
	}
	ptr[k] = 0;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;

	if (!s || !c)
		if (!s)
			return (0);
	if (!(*s))
	{
		ptr = (char **) malloc (2 * sizeof (char *));
		ptr[0] = 0;
		ptr[1] = 0;
	}
	else
		ptr = ft_fill(s, c);
	return (ptr);
}

int	main(void)
{
	pid_t	pid;
	int		r;
	char	**env;
	char	str[10000];
	char	*arg[] = {"echo", "ciao", "come", "stai", "?"};
	int		link[2];

	pipe(link);
	pid = fork();
	if (pid == 0)
	{
		dup2(link[1], 1);
		close(link[0]);
		close(link[1]);
		env = ft_split(getenv("PATH"), ':');
		execve("/bin/echo", arg, env);
	}
	else
	{
		close(link[1]);
		r = read(link[0], str, 10000);
		str[r] = 0;
	}
	printf("%s", str);
	printf("%d\n", access("/bin/ciao", 0));
	return (0);
}
