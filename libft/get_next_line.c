/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:28:03 by hajmoham          #+#    #+#             */
/*   Updated: 2025/10/08 12:16:57 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_fd(int fd, char *temp_str, char *str)
{
	int		size;
	char	*s;

	size = 1;
	while ((!ft_strchr(str, '\n')) && size > 0)
	{
		size = read(fd, temp_str, BUFFER_SIZE);
		if (size < 0)
		{
			free(str);
			free(temp_str);
			return (NULL);
		}
		if (size == 0)
		{
			free(temp_str);
			return (str);
		}
		temp_str[size] = '\0';
		s = str;
		str = ft_strjoin(str, temp_str);
		free(s);
	}
	free(temp_str);
	return (str);
}

char	*existing_line(char *str)
{
	char	*exist_line;
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	exist_line = malloc(i + 1);
	if (!exist_line)
		return (NULL);
	exist_line[i] = '\0';
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		exist_line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		exist_line[i] = '\n';
	return (exist_line);
}

char	*next_line(char *str)
{
	size_t	i;
	char	*next_str;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	next_str = ft_strdup(str + i);
	if (!next_str)
		return (NULL);
	free(str);
	return (next_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;
	char		*temp_str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	temp_str = malloc((size_t)BUFFER_SIZE + 1);
	if (!temp_str)
		return (NULL);
	str = read_fd(fd, temp_str, str);
	if (!str)
		return (NULL);
	line = existing_line(str);
	str = next_line(str);
	return (line);
}
