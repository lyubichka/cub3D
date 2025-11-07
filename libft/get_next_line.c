/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:44:13 by vlyubick          #+#    #+#             */
/*   Updated: 2025/10/30 23:54:12 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_savestr(char *st_str)
{
	int		i;
	char	*after;

	i = 0;
	after = NULL;
	while (st_str[i] != '\n' && st_str[i] != '\0')
		i++;
	if (st_str[i] == '\0')
		after = NULL;
	else
		after = gnl_strjoin(after, &st_str[i + 1]);
	free (st_str);
	st_str = NULL;
	return (after);
}

char	*ft_anl(char *st_str)
{
	int		i;
	char	*tmp;
	char	c;

	if (!st_str)
		return (NULL);
	i = 0;
	while (st_str[i] != '\n' && st_str[i] != '\0')
		i++;
	if (st_str[i] == '\0')
	{
		tmp = gnl_strjoin(NULL, st_str);
		return (tmp);
	}
	c = st_str[i + 1];
	st_str[i + 1] = '\0';
	tmp = gnl_strjoin(NULL, st_str);
	st_str[i + 1] = c;
	return (tmp);
}

char	*ft_read(char *st_str, int fd)
{
	char	buff[BUFFER_SIZE + 1];
	int		r;

	r = 0;
	while (findn(st_str) == 0)
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r < 1)
			break ;
		buff[r] = '\0';
		st_str = gnl_strjoin(st_str, buff);
	}
	return (st_str);
}

char	*get_next_line(int fd)
{
	static char	*st_str;
	char		*line;

	line = NULL;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 0)
		return (NULL);
	st_str = ft_read(st_str, fd);
	if (st_str == NULL)
		return (NULL);
	line = ft_anl(st_str);
	st_str = ft_savestr(st_str);
	if (line && line[0] == '\0')
	{
		free(line);
		line = NULL;
	}
	return (line);
}
