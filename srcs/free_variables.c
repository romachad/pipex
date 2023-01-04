/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 03:40:42 by romachad          #+#    #+#             */
/*   Updated: 2023/01/04 03:43:35 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

int	free_args(t_pipex *args)
{
	free(args->infile);
	free(args->outfile);
	free(args->cmd_str);
	return (4);
}

void	*free_char_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	return (0);
}
