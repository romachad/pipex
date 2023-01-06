/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 02:30:45 by romachad          #+#    #+#             */
/*   Updated: 2023/01/06 05:49:42 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/libft.h"
#include "../headers/ft_printf.h"

static int	call_fork(int *pipe, t_pipex *args, char *envp[])
{
	args->pid[args->cmd_n - 2] = fork();
	if (args->pid[args->cmd_n - 2] == -1)
		return (free_args(args) - 6);
	if (args->pid[args->cmd_n - 2] == 0)
	{
		args->pid[args->cmd_n - 2] = child_prog(pipe, args, envp);
		free_args(args);
		exit (1);
	}
	if (args->pid[args->cmd_n - 2] > 0)
		return (0);
	else
		return (-1);
}

static void	bonus(int *pipe, t_pipex *args, char *argv[], char *envp[])
{
	int	retv;
	int	i;

	args->flag = 2;
	i = - 1;
	while (++i < args->qtd_cmd - 2)
	{
		free(args->cmd_str);
		args->cmd_str = ft_strdup(argv[args->cmd_n]);
		retv = call_fork(pipe, args, envp);
		if (retv < 0)
		{
			free_args(args);
			exit (255);
		}
		args->cmd_n++;
	}
}

static int	main_fork(int *pipe, t_pipex *args, char *argv[], char *envp[])
{
	int	retv;

	args->flag = 0;
	retv = call_fork(pipe, args, envp);
	if (retv < 0)
	{
		free_args(args);
		exit (255);
	}
	args->cmd_n++;
	if (args->qtd_cmd > 2)
		bonus(pipe, args, argv, envp);
	free(args->cmd_str);
	args->cmd_str = ft_strdup(argv[args->argc - 2]);
	args->flag = 1;
	retv = call_fork(pipe, args, envp);
	if (retv < 0)
		perror("pipex error ");
	close(pipe[0]);
	close(pipe[1]);
	waitpid(args->pid[0], NULL, 0);
	waitpid(args->pid[1], NULL, 0);
	free_args(args);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	arguments;
	int		p1[2];

	if (argc < 5)
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
	arguments.outfile = ft_strdup(argv[argc - 1]);
	arguments.argc = argc;
	arguments.qtd_cmd = argc - 3;
	arguments.pid = malloc(arguments.qtd_cmd * sizeof(int));
	arguments.cmd_n = 2;
	arguments.cmd_str = ft_strdup(argv[2]);
	return (main_fork(p1, &arguments, argv, envp));
}
