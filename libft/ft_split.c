/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:14:55 by hajmoham          #+#    #+#             */
/*   Updated: 2024/08/07 16:56:08 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	my_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			count++;
		}
		i++;
	}
	return (count);
}

char	*cpy_word(char const *s, char c, char *str)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = ft_calloc((i + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s, i);
	return (str);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**allocation(char **array, char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = my_count(s, c);
	array = ((malloc(sizeof(char *) * (count + 1))));
	if (!array)
		return (NULL);
	i = 0;
	while (i < count)
	{
		while (*s == c)
			s++;
		array[i] = cpy_word(s, c, array[i]);
		if (!array[i])
		{
			free_array(array);
			return (NULL);
		}
		while (*s && *s != c)
			s++;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	array = NULL;
	if (s == NULL)
	{
		return (NULL);
	}
	array = allocation(array, s, c);
	return (array);
}
