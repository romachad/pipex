/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_str_treatment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 03:44:48 by romachad          #+#    #+#             */
/*   Updated: 2023/01/04 03:54:27 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/libft.h"

static void	treat_quotes(char *str)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (str[++i])
	{
		if ((str[i] == '"' && str[i - 1] != '\\') \
				|| (str[i] == 39 && str[i - 1] != '\\'))
		{
			if (flag == 1)
				flag = 0;
			else
				flag = 1;
			str[i] = 18;
		}
		if (flag == 1 && str[i] == ' ')
			str[i] = 17;
	}
}

static void	add_space(char **str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == 17)
				str[i][j] = ' ';
		}
	}
}

char	**treat_str(char *str)
{
	char	*t_str;
	char	**str_treated;
	char	set[2];
	int		i;

	set[0] = 18;
	set[1] = 0;
	treat_quotes(str);
	str_treated = ft_split(str, ' ');
	i = -1;
	while (str_treated[++i])
	{
		t_str = ft_strtrim(str_treated[i], set);
		if (t_str[0] == 0)
			free(t_str);
		else
		{
			free(str_treated[i]);
			str_treated[i] = t_str;
		}
	}
	add_space(str_treated);
	return (str_treated);
}
