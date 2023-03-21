#include "minishell.h"

int	main(void)
{
	char	*str;

	str = getenv("OLDPWD");
	if (str)
		printf("%s\n", str);
	else
		printf("nonono\n");
}
