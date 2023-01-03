/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 03:50:29 by romachad          #+#    #+#             */
/*   Updated: 2023/01/03 06:05:41 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/libft.h"
#include "../headers/ft_printf.h"

static int	child_infile_outpipe(int *pipe, t_pipex *args, char **envp)
{
	int	fd;

	fd = open(args->infile, O_RDONLY);
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		close(pipe[0]);
		dup2(pipe[1], STDOUT_FILENO);
		close(pipe[1]);
		execve(args->fpath, args->cmd_args, envp);
	}
	free(args->fpath);
	free_char_array(args->cmd_args);
	return (3);
}

static int	child_inpipe_outfile(int *pipe, t_pipex *args, char **envp)
{
	int	fd;

	close(pipe[1]);
	fd = open(args->outfile, O_WRONLY);
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
		dup2(pipe[0], STDIN_FILENO);
		close(pipe[0]);
		execve(args->fpath, args->cmd_args, envp);
	}
	free(args->fpath);
	free_char_array(args->cmd_args);
	return (4);
}

static int	child_exec(int *pipe, t_pipex *args, char **envp)
{
	if (args->flag == 0)
		return (child_infile_outpipe(pipe, args, envp));
	if (args->flag == 1)
	{
		return (child_inpipe_outfile(pipe, args, envp));
	}
	else
	{
		ft_printf("Nothing here!\n");
		free(args->fpath);
		free_char_array(args->cmd_args);
		return (255);
	}
}

static char	**treat_str(char *str)
{
	char	*t_str;
	char	**str_treated;
	char	set[2];
	int		i;

	set[0] = 18;
	set[1] = 0;
	treat_quotes(str);
	//free(str);
	str_treated = ft_split(str, ' ');
	free(str);
	i = -1;
	while (str_treated[++i])
	{
		t_str = ft_strtrim(str_treated[i], set);
		if (t_str[0] == 0)
			free(t_str);
		else
		{
			free(str_treated[i]);
			str_treated[i] = t_str;
		}
	}
	//t_str = ft_strtrim(str, set);
	add_space(str_treated);
	//free(t_str);
	return (str_treated);
}

int	child_prog(int *pipe, t_pipex *args, char **envp)
{
	if (args->flag == 0)
	{
		if (check_infile(args->infile) != 0)
			return (6);
	}
	if (args->flag == 1)
	{
		if (check_outfile(args->outfile) != 0)
			return (5);
	}
	args->cmd_args = treat_str(args->cmd_str);
	args->fpath = path_search(envp, args->cmd_args[0]);
	if (args->fpath == NULL)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		ft_printf("pipex: %s not found\n", args->cmd_args[0]);
		free_char_array(args->cmd_args);
		return (127);
	}
	return (child_exec(pipe, args, envp));
}
