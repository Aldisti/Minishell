#include "../minishell.h"

char	**ft_redup(char **files, char *str, int *dim)
{
	char	**tmp;

	tmp = (char **) ft_realloc(files, sizeof(char *), *dim, *dim + 1);
	if (!tmp)
	{
		ft_free_mat((void ***) &files);
		return (NULL);
	}
	files = tmp;
	(*dim)++;
	files[*dim - 2] = ft_strdup(str);
	if (!files[*dim - 2])
	{
		ft_free_mat((void ***) &files);
		return (NULL);
	}
	return (files);
}

char	**ft_get_files(DIR *dirp, struct dirent *dir, char **files)
{
	int		dim;

	dim = 1;
	files = NULL;
	files = (char **) ft_realloc(files, sizeof(char *), 0, dim);
	if (!files)
		return (NULL);
	while (dir)
	{
		files = ft_redup(files, dir->d_name, &dim);
		if (!files)
			return (NULL);
		errno = 0;
		dir = readdir(dirp);
		if (errno && !dir)
		{
			ft_free_mat((void ***) &files);
			perror("Error");
			return (NULL);
		}
	}
	return (files);
}

char	**ft_readdir(char *path)
{
	DIR		*dirp;
	struct dirent	*dir;
	char		**files;
	
	dirp = opendir(path);
	if (!dirp)
	{
		perror("Error");
		return (NULL);
	}
	errno = 0;
	dir = readdir(dirp);
	if (errno && !dir)
	{
		perror("Error");
		return (NULL);
	}
	files = ft_get_files(dirp, dir, files);
	if (closedir(dirp) == -1)
	{
		perror("Error");
		ft_free_mat((void ***) &files);
		return (NULL);
	}
	return (files);
}
