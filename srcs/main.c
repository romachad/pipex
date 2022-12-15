/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 02:30:45 by romachad          #+#    #+#             */
/*   Updated: 2022/12/15 01:30:05 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/libft.h"
#include "../headers/ft_printf.h"

#include <sys/wait.h>
int	main(int argc, const char *argv[], char *envp[])
{
	int	fd;
	char	**cmd1;
	char	*fpath;
	//int i;

	cmd1 = ft_split(argv[2], ' ');
	fpath = path_search(envp, cmd1[0]);
	if (fpath == NULL)
	{
		ft_printf("COMMAND %s NOT FOUND!\n", cmd1[0]);
		//free(fpath);
		free_char_array(cmd1);
		return 127;
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
		free(fpath);
		free_char_array(cmd1);
		return (3);
	}
	else
	{
		//PARENT
		ft_printf("I am fd %d!\n", fd);
	}
	wait(0);
	free(fpath);
	free_char_array(cmd1);
	ft_printf("Still alive: %d\n", fd);
	return 0;
}
