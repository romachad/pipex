/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_perm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 03:41:24 by romachad          #+#    #+#             */
/*   Updated: 2022/12/31 20:09:06 by coret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/ft_printf.h"
#include "../headers/libft.h"

/*int	check_perm(const char *file, int mode)
{
	char	*str;
	int		fd;

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
	char	*str;
	int		error;
	int		fd;

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
	fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (fd == -1)
	{
		str = ft_strjoin("pipex: ", argv[4]);
		perror(str);
		free(str);
		error = 2;
	}
	else
		close(fd);
	return (error);
}*/

int	check_outfile(char *outfile)
{
	char	*str;
	int		fd;

	fd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (fd == -1)
	{
		str = ft_strjoin("pipex: ", outfile);
		perror(str);
		free(str);
		return (5);
	}
	close(fd);
	return (0);
}

int	check_infile(char *infile)
{
	char	*str;
	int		fd;

	fd = access(infile, R_OK);
	if (fd == -1)
	{
		str = ft_strjoin("pipex: ", infile);
		perror(str);
		free(str);
		return (6);
	}
	return (0);
}
