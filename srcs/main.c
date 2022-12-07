/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 02:30:45 by romachad          #+#    #+#             */
/*   Updated: 2022/12/07 04:28:59 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/ft_printf.h"

#include <fcntl.h>

int	main(int argc, const char *argv[])
{
	return (check_files(argc, argv));
	/*int	error;
	int	fd;

	error = 0;
	if (argc != 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	if (check_perm(argv[1], R_OK))
	{
		error = 1;
	}
	fd = open(argv[4], O_CREAT|O_RDWR|O_TRUNC, 0664);
	if (fd == -1)
	{
		perror(argv[4]);
		error = 1;
	}
	else
		close(fd);
	return (error);*/
}
