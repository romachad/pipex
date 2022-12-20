/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 02:35:00 by romachad          #+#    #+#             */
/*   Updated: 2022/12/18 00:59:59 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/libft.h"

static size_t	count_char(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	while (s[i] == c && s[i])
		i++;
	count = 0;
	while (s[i] != 0)
	{
		count++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

static void	*free_array(char **array, size_t i)
{
	while (i > 0)
	{
		free(array[i]);
		i--;
	}
	free(array[i]);
	free(array);
	return (0);
}

static char	**make_array(char **array, size_t count, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	size = 0;
	while (s[i] && j < count)
	{
		while (s[i] == c && s[i] != 0)
			i++;
		while (s[i] != c && s[i] != 0)
		{
			size++;
			i++;
		}
		array[j] = ft_substr(&s[i - size], 0, size);
		if (array[j] == 0)
			return (free_array(array, j));
		size = 0;
		j++;
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**array;

	if (!s)
		return (ft_calloc(1, sizeof(char)));
	if (s == 0 || !ft_isascii(c))
		return (0);
	count = count_char(s, c);
	if (count > 0)
		array = (char **) malloc((count + 1) * sizeof(char *));
	else
	{
		array = (char **) ft_calloc(1, sizeof(char *));
		return (array);
	}
	if (!array)
		return (0);
	else
	{
		array = make_array(array, count, s, c);
		array[count] = 0;
		return (array);
	}
}
