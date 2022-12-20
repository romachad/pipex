/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 03:45:20 by romachad          #+#    #+#             */
/*   Updated: 2022/12/18 00:57:20 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;
	size_t	mem_size;

	if (nmemb == 0 || size == 0)
		return (0);
	mem_size = nmemb * size;
	if (mem_size / nmemb != size)
		return (0);
	mem = malloc(mem_size);
	if (!mem)
		return (0);
	ft_bzero(mem, (nmemb * size));
	return (mem);
}
