/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 07:52:30 by romachad          #+#    #+#             */
/*   Updated: 2022/12/18 00:59:25 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*dest_original;
	char	*swap;
	size_t	diff;

	if ((src + n) > dest && src < dest)
	{
		dest_original = dest;
		diff = (dest - src);
		dest = (char *) src + n - 1 + diff;
		while (n > 0)
		{
			swap = (char *) dest - diff;
			ft_memset(dest, swap[0], 1);
			dest--;
			n--;
		}
	}
	else
		return (ft_memcpy(dest, src, n));
	return (dest_original);
}
