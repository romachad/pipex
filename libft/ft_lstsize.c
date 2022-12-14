/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 05:49:29 by romachad          #+#    #+#             */
/*   Updated: 2022/06/29 08:15:27 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*swap;

	if (!lst)
		return (0);
	i = 0;
	swap = lst;
	while (swap)
	{
		swap = swap->next;
		i++;
	}
	return (i);
}
