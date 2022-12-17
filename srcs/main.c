/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 02:30:45 by romachad          #+#    #+#             */
/*   Updated: 2022/12/17 06:53:23 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/libft.h"
#include "../headers/ft_printf.h"

int	main(int argc, const char *argv[], char *envp[])
{
	int	pid;
	int	pid2;
	int p1[2];
	t_pipex	arguments;

	if ((check_files(argc, argv)))
	{
		return 2;
	}

	if (pipe(p1) == -1)
	{
		ft_printf("Fail to create pipe!\n");
		return (130);
	}

	arguments.infile = ft_strdup(argv[1]);
	arguments.outfile = ft_strdup(argv[4]);
	arguments.cmd_str = ft_strdup(argv[2]);
	
	pid = fork();
	if (pid == -1)
	{
		//FALHA no FORK
		free(arguments.infile);
		free(arguments.outfile);
		free(arguments.cmd_str);
		return (3);
	}
	if (pid == 0)
	{
		pid = child_prog(p1, 0, &arguments, envp);
		free(arguments.infile);
		free(arguments.outfile);
		free(arguments.cmd_str);
		return (pid);
	}
	free(arguments.cmd_str);
	arguments.cmd_str = ft_strdup(argv[3]);
	pid2 = fork();
	if (pid2 == -1)
	{
		wait(NULL);
		//FALHA no FORK
		free(arguments.infile);
		free(arguments.outfile);
		free(arguments.cmd_str);
		return (4);
	}
	if (pid2 == 0)
	{
		pid2 = child_prog(p1, 1, &arguments, envp);
		free(arguments.infile);
		free(arguments.outfile);
		free(arguments.cmd_str);
		return (pid2);
	}
	close(p1[0]);
	close(p1[1]);
	//Adicionar wait para cara PID!
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	free(arguments.infile);
	free(arguments.outfile);
	free(arguments.cmd_str);
	//ft_printf("Still alive: %d\n", pid);
	return 0;
}
