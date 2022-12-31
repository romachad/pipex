/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 03:50:29 by romachad          #+#    #+#             */
/*   Updated: 2022/12/31 02:46:38 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/libft.h"
#include "../headers/ft_printf.h"

static int	child_infile_outpipe(int *pipe, t_pipex *args, char **envp)
{
	int	fd;

	fd = open(args->infile, O_RDONLY);
	if (fd == -1)
		return (3);
	dup2(fd, STDIN_FILENO);
	close(fd);
	close(pipe[0]);

	ft_printf("\nINfile OUTpipe! fd: %i\n", fd);
	ft_printf("NANI??\n");

	dup2(pipe[1], STDOUT_FILENO);

	ft_printf("dup2 pipe[1] to stdout!\n");

	close(pipe[1]);

	ft_printf("closei o pipe[1]!\n");

	execve(args->fpath, args->cmd_args, envp);
	dup2(STDOUT_FILENO, STDERR_FILENO);
	ft_printf("deu rum se vc esta lendo\n");
	free(args->fpath);
	free_char_array(args->cmd_args);
	return (3);
}

static int	child_inpipe_outfile(int *pipe, t_pipex *args, char **envp)
{
	int	fd;

	close(pipe[1]);
	fd = open(args->outfile, O_WRONLY);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(pipe[0], STDIN_FILENO);
	close(pipe[0]);
	execve(args->fpath, args->cmd_args, envp);
	dup2(STDOUT_FILENO, STDERR_FILENO);
	ft_printf("Deu ruim, read pipe to outfile\n");
	free(args->fpath);
	free_char_array(args->cmd_args);
	return (4);
}

static int	child_exec(int *pipe, int flag, t_pipex *args, char **envp)
{
	if (flag == 0)
		return (child_infile_outpipe(pipe, args, envp));
	if (flag == 1)
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

int	child_prog(int *pipe, int flag, t_pipex *args, char **envp)
{
	args->cmd_args = ft_split(args->cmd_str, ' ');
	args->fpath = path_search(envp, args->cmd_args[0]);
	if (args->fpath == NULL)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		ft_printf("pipex: %s not found\n", args->cmd_args[0]);
		free_char_array(args->cmd_args);
		return (127);
	}
	return (child_exec(pipe, flag, args, envp));
}
