/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_perm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 03:41:24 by romachad          #+#    #+#             */
/*   Updated: 2022/12/07 04:30:10 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/ft_printf.h"

int	check_perm(const char *file, int mode)
{
	int	fd;
	char	*str;

	fd = access(file, mode);
	if (fd == -1 && mode != F_OK)
	{
		str = ft_strjoin("pipex: ", file);
		perror(str);
		free(str);
		return (1);
	}
	else if (fd == -1 && mode == F_OK)
		return (1);
	else
		return (0);
}

int	check_files(int argc, const char *argv[])
{
	int	error;
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
	return (error);
}
