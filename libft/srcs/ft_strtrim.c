/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:15:48 by romachad          #+#    #+#             */
/*   Updated: 2022/12/18 01:00:56 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	full_size;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	full_size = ft_strlen(s1);
	if (!full_size)
		return (ft_calloc(1, sizeof(char)));
	if (!(ft_strlen(set)))
		return (ft_strdup(s1));
	i = 0;
	while (ft_strchr(set, s1[i]) && s1[i])
		i++;
	if (i == full_size)
		return (ft_calloc(1, sizeof(char)));
	while (ft_strrchr(set, s1[full_size]))
		full_size--;
	return (ft_substr(s1, i, (full_size - i + 1)));
}
