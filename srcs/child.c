/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 03:50:29 by romachad          #+#    #+#             */
/*   Updated: 2022/12/17 07:08:15 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/libft.h"
#include "../headers/ft_printf.h"

static int	child_exec(int *pipe, int flag, t_pipex *args, char **envp)
{
	int	fd_local;

	if (flag == 0)
	{
		fd_local = open(args->infile, O_RDONLY);
		dup2(fd_local, STDIN_FILENO);
		close(fd_local);
		close(pipe[0]);
		//bkp_stdout = dup(STDOUT_FILENO);
		dup2(pipe[1], STDOUT_FILENO);
		close(pipe[1]);
		execve(args->fpath, args->cmd_args, envp);
		dup2(STDOUT_FILENO, STDERR_FILENO);
		//ft_printf("Deu ruim se vc esta lendo\n");
		free(args->fpath);
		free_char_array(args->cmd_args);
		return (3);
	}
	if (flag == 1)
	{
		//ft_printf("child, fpath: %s ; args[0]: %s\n",args->fpath, args->cmd_args[0]);
		close(pipe[1]);
		fd_local = open(args->outfile, O_WRONLY);
		dup2(fd_local, STDOUT_FILENO);
		close(fd_local);
		dup2(pipe[0], STDIN_FILENO);
		close(pipe[0]);
		execve(args->fpath, args->cmd_args, envp);
		dup2(STDOUT_FILENO, STDERR_FILENO);
		//ft_printf("Deu ruim, read pipe to outfile, se vc esta lendo\n");
		free(args->fpath);
		free_char_array(args->cmd_args);
		return (4);
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
		return 127;
	}
	return (child_exec(pipe, flag, args, envp));
}
