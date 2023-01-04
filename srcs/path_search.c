/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 00:00:09 by romachad          #+#    #+#             */
/*   Updated: 2023/01/04 03:17:17 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/libft.h"

int	free_args(t_pipex *args)
{
	free(args->infile);
	free(args->outfile);
	free(args->cmd_str);
	return (4);
}

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

void	treat_quotes(char *str)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (str[++i])
	{
		if ((str[i] == '"' && str[i - 1] != '\\') \
				|| (str[i] == 39 && str[i - 1] != '\\'))
		{
			if (flag == 1)
				flag = 0;
			else
				flag = 1;
			str[i] = 18;
		}
		if (flag == 1 && str[i] == ' ')
			str[i] = 17;
	}
}

void	add_space(char **str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == 17)
				str[i][j] = ' ';
		}
	}
}
