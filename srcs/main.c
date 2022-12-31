/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 02:30:45 by romachad          #+#    #+#             */
/*   Updated: 2022/12/31 20:17:35 by coret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/libft.h"
#include "../headers/ft_printf.h"

int	main_fork(int *pipe, t_pipex *args, const char *argv[], char *envp[])
{
	int	pid;
	int	pid2;

	pid = fork();
	if (pid == -1)
		return (free_args(args));
	if (pid == 0)
	{
		pid = child_prog(pipe, 0, args, envp);
		free_args(args);
		return (pid);
	}
	free(args->cmd_str);
	args->cmd_str = ft_strdup(argv[3]);
	pid2 = fork();
	if (pid2 == -1)
	{
		wait(NULL);
		return (free_args(args));
	}
	if (pid2 == 0)
	{
		pid2 = child_prog(pipe, 1, args, envp);
		free_args(args);
		return (pid2);
	}
	close(pipe[0]);
	close(pipe[1]);
	//Adicionar wait para cara PID!
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_args(args);
	return (0);
}

int	main(int argc, const char *argv[], char *envp[])
{
	int	p1[2];
	t_pipex	arguments;

	if (argc != 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (3);
	}
	if (pipe(p1) == -1)
	{
		ft_printf("Fail to create pipe!\n");
		return (130);
	}
	arguments.infile = ft_strdup(argv[1]);
	arguments.outfile = ft_strdup(argv[4]);
	arguments.cmd_str = ft_strdup(argv[2]);
	return (main_fork(p1, &arguments, argv, envp));
}
