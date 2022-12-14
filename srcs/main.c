/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 02:30:45 by romachad          #+#    #+#             */
/*   Updated: 2022/12/14 05:44:46 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/ft_printf.h"

#include <sys/wait.h>
int	main(int argc, const char *argv[], char *envp[])
{
	int	fd;
	char	**cmd1;
	int i;

	cmd1 = ft_split(argv[2], ' ');
	
	/*for (i = 0;  envp[i] != 0; i++)
		ft_printf("env %d: %s\n",i, envp[i]);*/

	i = -1;
	while (envp[++i])
	{
		if (!(ft_strncmp(envp[i], "PATH=", 5)))
			break ;
	}
	//ft_printf("I eh igual a: %d\n", i);

	char *path;
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	//ft_printf("Full path is: %s\n\n", path);

	char **paths;
	paths = ft_split(path, ':');
	free(path);

	//for (i=0; paths[i] ; i++)
	//	ft_printf("path %d: %s\n",i, paths[i]);
	//ft_printf("\n");

	char *ppath, *fpath;
	int x_flag;
	ppath = ft_strjoin("/", cmd1[0]);
	i = -1;
	while (paths[++i])
	{
		fpath = ft_strjoin(paths[i], ppath);
		x_flag = access(fpath, X_OK);
		/*if (x_flag == -1)
			ft_printf("fail test to exec at: %s\n",fpath);
		else
			ft_printf("OK exec at: %s\n", fpath);*/
		if (x_flag == 0)
			break ;
		free(fpath);
	}
	if (x_flag == -1) //check local path!
	{
		fpath = ft_strjoin(".", ppath);
		x_flag = access(fpath, X_OK);
	}
	if (x_flag == -1)
	{
		ft_printf("UNABLE TO ACCESS CMD: %s\n", cmd1[0]);
		return (127);
	}



	if ((check_files(argc, argv)))
		return 2;
	fd = fork();
	if (fd == -1)
		//FALHA no FORK
		return (3);
	if (fd == 0)
	{
		//CHILD!
		ft_printf("I am fd zero!\n");
		execve(fpath, cmd1, envp);
		ft_printf("Deu ruim se vc esta me lendo!\n");
		return (3);
	}
	else
	{
		//PARENT
		ft_printf("I am fd %d!\n", fd);
	}
	wait(0);
	ft_printf("Still alive: %d\n", fd);
	return 0;
}
