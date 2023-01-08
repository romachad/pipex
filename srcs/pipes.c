/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 06:21:30 by romachad          #+#    #+#             */
/*   Updated: 2023/01/08 06:31:21 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	close_pipes(t_pipex *args)
{
	int	i;

	i = -1;
	while (++i < (args->qtd_cmd - 1) * 2)
		close(args->pipes[i]);
}

int	create_pipes(t_pipex *args)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < args->qtd_cmd -1)
	{
		if (pipe(&args->pipes[j]) == -1)
			return (-1);
		j += 2;
	}
	return (0);
}
