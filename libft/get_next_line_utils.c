/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:08:36 by vlyubick          #+#    #+#             */
/*   Updated: 2025/11/26 02:59:08 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	gnl_strlen(const char *s)
{
	if (s == NULL)
		return (0);
	return (ft_strlen(s));
}

int	findn(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static void	copy_strings(char *str, char *s1, char *s2, int *lens)
{
	int	i;
	int	j;

	i = 0;
	while (i < lens[0])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < lens[1])
	{
		str[i + j] = s2[j];
		j++;
	}
}

char	*gnl_strjoin(char *s1, char *s2)
{
	int		lens[2];
	char	*str;

	lens[0] = (int)gnl_strlen(s1);
	lens[1] = (int)gnl_strlen(s2);
	str = (char *)malloc((lens[0] + lens[1] + 1) * sizeof(char));
	if (!str)
		return (NULL);
	copy_strings(str, s1, s2, lens);
	str[lens[0] + lens[1]] = '\0';
	if (s1)
		free(s1);
	return (str);
}
