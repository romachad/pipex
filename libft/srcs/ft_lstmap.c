/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 00:01:15 by romachad          #+#    #+#             */
/*   Updated: 2022/12/18 00:58:52 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_lst;
	t_list	*new;
	void	*result;

	if (!lst)
		return (NULL);
	n_lst = NULL;
	new = NULL;
	while (lst)
	{
		result = f(lst->content);
		new = ft_lstnew(result);
		if (!new)
		{
			ft_lstclear(&new, del);
			ft_lstclear(&n_lst, del);
			return (NULL);
		}
		else
			ft_lstadd_back(&n_lst, new);
		lst = lst->next;
	}
	return (n_lst);
}
