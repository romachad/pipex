/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 00:00:09 by romachad          #+#    #+#             */
/*   Updated: 2022/12/31 01:55:39 by romachad         ###   ########.fr       */
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
	char	*tmppath;
	int		i;
	int		x_flag;

	i = -1;
	while (paths[++i])
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
		return (NULL);
}

char	*path_search(char *envp[], const char *cmd)
{
	char	*path;
	char	*tmppath;
	char	**paths;
	int		i;

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
	paths = ft_split(path, ':');
	free(path);
	path = exec_val(paths, ft_strjoin("/", cmd));
	free_char_array(paths);
	return (path);
}
