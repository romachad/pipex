/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 02:30:45 by romachad          #+#    #+#             */
/*   Updated: 2023/01/04 03:16:00 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/libft.h"
#include "../headers/ft_printf.h"

static int	call_fork(int *pipe, t_pipex *args, char *envp[])
{
	args->pid[args->flag] = fork();
	if (args->pid[args->flag] == -1)
		return (free_args(args) + 1);
	if (args->pid[args->flag] == 0)
	{
		args->pid[args->flag] = child_prog(pipe, args, envp);
		return (args->pid[args->flag]);
	}
	if (args->pid[args->flag] > 0)
		return (0);
	else
		return (-1);
}

static int	main_fork(int *pipe, t_pipex *args, char *argv[], char *envp[])
{
	int	retv;

	args->flag = 0;
	retv = call_fork(pipe, args, envp);
	if (retv < 0)
		return (255);
	free(args->cmd_str);
	args->cmd_str = ft_strdup(argv[3]);
	args->flag = 1;
	retv = call_fork(pipe, args, envp);
	if (retv < 0)
		return (255);
	close(pipe[0]);
	close(pipe[1]);
	waitpid(args->pid[0], NULL, 0);
	waitpid(args->pid[1], NULL, 0);
	free_args(args);
	return (0);
}

int	main(int argc, const char *argv[], char *envp[])
{
	t_pipex	arguments;
	int		p1[2];

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
