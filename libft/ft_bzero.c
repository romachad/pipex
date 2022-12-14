/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 06:58:03 by romachad          #+#    #+#             */
/*   Updated: 2022/06/29 02:53:30 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*replace;

	if (!s)
		return ;
	replace = (char *) s;
	i = 0;
	while (i < n)
	{
		replace[i] = 0;
		i++;
	}
}
