/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 19:50:07 by romachad          #+#    #+#             */
/*   Updated: 2022/05/29 20:51:25 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_toupper(int c)
{
	if (c < -128 || c > 255 || c == -1)
		return (c);
	if (c >= 'a' && c <= 'z')
		return ((unsigned char) c - 32);
	else
		return ((unsigned char) c);
}
