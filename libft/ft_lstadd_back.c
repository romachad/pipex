/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 06:30:23 by romachad          #+#    #+#             */
/*   Updated: 2022/06/29 06:44:26 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*swap;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		swap = ft_lstlast(*lst);
		swap->next = new;
	}
}
