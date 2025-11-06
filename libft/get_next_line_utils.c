/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:08:36 by vlyubick          #+#    #+#             */
/*   Updated: 2025/10/31 00:08:07 by veronikalub      ###   ########.fr       */
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

char	*gnl_strjoin(char *s1, char *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*str;

	len1 = (int)gnl_strlen(s1);
	len2 = (int)gnl_strlen(s2);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	int j = 0;
	while (j < len2)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[len1 + len2] = '\0';
	if (s1)
		free(s1);
	return (str);
}
