/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 03:50:29 by romachad          #+#    #+#             */
/*   Updated: 2023/01/06 06:02:25 by romachad         ###   ########.fr       */
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

static void	child_inpipe_outpipe(int *pipe, t_pipex *args, char **envp)
{
	//int	bkp_fd1;
	//int	bkp_fd2;

	//if (args->qtd_cmd % 2 != 0)
	if (args->cmd_n % 2 == 0)
	{
		//bkp_fd1 = dup(pipe[0]);
		//bkp_fd2 = dup(pipe[1]);
		dup2(pipe[1], STDIN_FILENO);
		dup2(pipe[0], STDOUT_FILENO);
	}
	else
	{
		dup2(pipe[0], STDIN_FILENO);
		dup2(pipe[1], STDOUT_FILENO);
	}
	//dup2(pipe[0], STDIN_FILENO);
	//dup2(pipe[1], STDOUT_FILENO);
	close(pipe[0]);
	close(pipe[1]);
	execve(args->fpath, args->cmd_args, envp);
	free(args->fpath);
	free_char_array(args->cmd_args);
	exit (254);
}

static int	child_inpipe_outfile(int *pipe, t_pipex *args, char **envp)
{
	int	fd;

	//close(pipe[1]);
	fd = open(args->outfile, O_WRONLY);
	//if (fd != -1 && args->qtd_cmd % 2 != 0)
	if (fd != -1)
	{
		close(pipe[1]);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		dup2(pipe[0], STDIN_FILENO);
		close(pipe[0]);
		execve(args->fpath, args->cmd_args, envp);
	}
	/*else if (fd != -1 && args->qtd_cmd % 2 == 0)
	{
		close(pipe[0]);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		dup2(pipe[1], STDIN_FILENO);
		close(pipe[1]);
		execve(args->fpath, args->cmd_args, envp);
	}*/
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
		child_inpipe_outpipe(pipe, args, envp);
		return (0);
		/*ft_printf("Nothing here!\n");
		free(args->fpath);
		free_char_array(args->cmd_args);
		return (255);*/
	}
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
