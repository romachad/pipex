/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 00:00:09 by romachad          #+#    #+#             */
/*   Updated: 2022/12/17 04:25:59 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/libft.h"

void	*free_char_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	return (0);
}

static char	*exec_val(char **paths, char *cmd)
{
	int	i;
	int	x_flag;
	char	*tmppath;

	i = -1;
	while(paths[++i])
	{
		tmppath = ft_strjoin(paths[i], cmd);
		x_flag = access(tmppath, X_OK);
		if (x_flag == 0)
			break ;
		free(tmppath);
	}
	free(cmd);
	if (x_flag == 0)
		return (tmppath);
	else
	{
		//free(tmppath);
		return (NULL);
	}
}

//#include "../headers/ft_printf.h"
char	*path_search(char *envp[], const char *cmd)
{
	int	i;
	char	*path;
	char	*tmppath;
	char	**paths;

	i = -1;
	while (envp[++i])
		if (!(ft_strncmp(envp[i], "PATH=", 5)))
			break ;
	if (envp[i])
	{
		tmppath = ft_strdup(envp[i]);
		path = ft_strjoin(tmppath, ":./");
		free(tmppath);
	}
	else
		path = ft_strdup(":./");
	//ft_printf("\npath is: %s\n", path);
	paths = ft_split(path, ':');
	free(path);
	path = exec_val(paths, ft_strjoin("/", cmd));
	free_char_array(paths);
	return (path);
}
