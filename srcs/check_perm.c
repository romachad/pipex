/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_perm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 03:41:24 by romachad          #+#    #+#             */
/*   Updated: 2023/01/08 07:28:06 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/ft_printf.h"
#include "../headers/libft.h"

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

int	check_args(int argc, char *argv[])
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (ft_strlen(argv[i]) == 0)
		{
			ft_printf("Error, argument can't be empty!\n");
			return (-1);
		}
	}
	return (0);
}
