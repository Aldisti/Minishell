/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:36:56 by marco             #+#    #+#             */
/*   Updated: 2023/04/17 22:37:03 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Description:	takes an array of strings and add a new string at the end.
 * Input:		files is the array of strings, which dimension (i.e. the 
 * 				number of strings including the NULL pointer) is dim,
 * 				str is the string to append.
 * Output:		on success returns the array with the new string at the end;
 * 				if an error occurs frees files and returns a NULL pointer.
*/
char	**ft_append(char **files, char *str, int *dim)
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

/*
 * Description:	gets all files in a directory and stores them in a strings
 * 				array.
 * Input:		dirp is a pointer to DIR (returned by opendir), dir is a
 * 				pointer to struct dirent (returned by readdir) and files
 * 				is an array of strings.
 * Output:		on success the function returns an array of strings filled
 * 				with the names of all files in the directory pointed by dirp;
 * 				if an error occures a NULL pointer is returned.
*/
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
		files = ft_append(files, dir->d_name, &dim);
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

/*
 * Description:	reads all files in a specified directory.
 * Input:		the relative or absolute directory path.
 * Output:		returns an array of strings allocated in
 * 				heap memory, free must be done.
 * 				If an error has occured the function returns
 * 				a NULL pointer.
*/
char	**ft_readdir(char *path)
{
	DIR				*dirp;
	struct dirent	*dir;
	char			**files;

	dirp = opendir(path);
	if (!dirp)
		return (NULL);
	errno = 0;
	dir = readdir(dirp);
	if (errno && !dir)
		return (NULL);
	files = NULL;
	files = ft_get_files(dirp, dir, files);
	if (closedir(dirp) == -1)
	{
		ft_free_mat((void ***) &files);
		return (NULL);
	}
	return (files);
}
