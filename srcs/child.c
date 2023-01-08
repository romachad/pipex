/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 03:50:29 by romachad          #+#    #+#             */
/*   Updated: 2023/01/08 06:37:40 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/libft.h"
#include "../headers/ft_printf.h"

static int	child_infile_outpipe(t_pipex *args, char **envp)
{
	int	fd;

	fd = open(args->infile, O_RDONLY);
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(args->pipes[1], STDOUT_FILENO);
		close_pipes(args);
		execve(args->fpath, args->cmd_args, envp);
	}
	free(args->fpath);
	free_char_array(args->cmd_args);
	return (3);
}

static void	child_inpipe_outpipe(t_pipex *args, char **envp)
{
	dup2(args->pipes[args->pipe_i], STDIN_FILENO);
	dup2(args->pipes[args->pipe_i + 3], STDOUT_FILENO);
	close_pipes(args);
	execve(args->fpath, args->cmd_args, envp);
	free(args->fpath);
	free_char_array(args->cmd_args);
	exit (254);
}

static int	child_inpipe_outfile(t_pipex *args, char **envp)
{
	int	fd;

	fd = open(args->outfile, O_WRONLY);
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
		dup2(args->pipes[args->pipe_i], STDIN_FILENO);
		close_pipes(args);
		execve(args->fpath, args->cmd_args, envp);
	}
	free(args->fpath);
	free_char_array(args->cmd_args);
	return (4);
}

static int	child_exec(t_pipex *args, char **envp)
{
	if (args->flag == 0)
		return (child_infile_outpipe(args, envp));
	if (args->flag == 1)
	{
		return (child_inpipe_outfile(args, envp));
	}
	else
	{
		child_inpipe_outpipe(args, envp);
		return (0);
	}
}

int	child_prog(t_pipex *args, char **envp)
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
	return (child_exec(args, envp));
}
