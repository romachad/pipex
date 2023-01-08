/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 02:30:45 by romachad          #+#    #+#             */
/*   Updated: 2023/01/08 07:20:36 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/libft.h"
#include "../headers/ft_printf.h"

static int	call_fork(t_pipex *args, char *envp[])
{
	args->pid[args->cmd_n - 1] = fork();
	if (args->pid[args->cmd_n - 1] == -1)
		return (free_args(args) - 6);
	if (args->pid[args->cmd_n - 1] == 0)
	{
		args->pid[args->cmd_n - 1] = child_prog(args, envp);
		free_args(args);
		exit (1);
	}
	if (args->pid[args->cmd_n - 1] > 0)
		return (0);
	else
		return (-1);
}

static void	bonus(t_pipex *args, char *argv[], char *envp[])
{
	int	retv;
	int	i;

	args->flag = 2;
	i = -1;
	while (++i < args->qtd_cmd - 2)
	{
		free(args->cmd_str);
		args->cmd_str = ft_strdup(argv[args->cmd_n + 1]);
		retv = call_fork(args, envp);
		if (retv < 0)
		{
			free_args(args);
			exit (255);
		}
		args->cmd_n++;
		args->pipe_i += 2;
	}
}

static int	main_fork(t_pipex *args, char *argv[], char *envp[])
{
	int	i;

	args->flag = 0;
	if (call_fork(args, envp) < 0)
	{
		free_args(args);
		exit (255);
	}
	args->cmd_n++;
	if (args->qtd_cmd > 2)
		bonus(args, argv, envp);
	free(args->cmd_str);
	args->cmd_str = ft_strdup(argv[args->argc - 2]);
	args->flag = 1;
	if (call_fork(args, envp) < 0)
		perror("pipex error ");
	close_pipes(args);
	i = -1;
	while (++i < args->cmd_n)
		waitpid(args->pid[i], NULL, 0);
	free_args(args);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	arguments;

	if (check_args(argc, argv) == -1)
		return (-1);
	if (argc < 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 cmdN file2\n");
		return (3);
	}
	arguments.qtd_cmd = argc - 3;
	arguments.pipes = malloc(((arguments.qtd_cmd - 1) * 2) * sizeof(int));
	if (create_pipes(&arguments) == -1)
	{
		ft_printf("ERROR! Fail to create pipes!\n");
		free(arguments.pipes);
		exit (130);
	}
	arguments.infile = ft_strdup(argv[1]);
	arguments.outfile = ft_strdup(argv[argc - 1]);
	arguments.argc = argc;
	arguments.pid = malloc(arguments.qtd_cmd * sizeof(int));
	arguments.cmd_n = 1;
	arguments.cmd_str = ft_strdup(argv[2]);
	arguments.pipe_i = 0;
	return (main_fork(&arguments, argv, envp));
}
