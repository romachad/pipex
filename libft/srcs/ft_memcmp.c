/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:50:55 by romachad          #+#    #+#             */
/*   Updated: 2022/12/18 00:59:12 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	if (!s1 || !s2)
		return (0);
	if (s1 == s2)
		return (0);
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (&str1[i] == s2)
			return (-1);
		if (&str2[i] == s1)
			return (1);
		if (((unsigned char) str1[i]) != ((unsigned char) str2[i]))
			return (((unsigned char) str1[i]) - ((unsigned char) str2[i]));
		i++;
	}
	return (0);
}
