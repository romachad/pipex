/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:35:44 by romachad          #+#    #+#             */
/*   Updated: 2022/12/18 01:00:23 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	size_d;
	size_t	size_s;
	size_t	i;

	if (!src || !dest)
		return (0);
	size_d = ft_strlen(dest);
	size_s = ft_strlen(src);
	if (size < size_d || size == 0)
		return (size_s + size);
	i = 0;
	while (((size_d + i) < (size - 1)) && src[i] != 0)
	{
		dest[size_d + i] = src[i];
		i++;
	}
	dest[size_d + i] = 0;
	if (dest <= src && (dest + size) >= src)
		return (size_d + size_s + i);
	else
		return (size_d + size_s);
}
