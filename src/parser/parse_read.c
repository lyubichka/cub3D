/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:16:19 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/18 17:11:24 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include <fcntl.h>
#include "../../libft/get_next_line.h"
// Первый проход: посчитать строки в файле
static int count_file_lines(const char *path)
{
    int fd;
    int n = 0;
    char *line;
    
    fd = open(path, O_RDONLY);
    if (fd < 0)
        print_error("Error: Unable to open .cub file");
    while ((line = get_next_line(fd)) != NULL)
    {
        free(line);
        n++;
    }
    close(fd);
    return(n);
}

static char **malloc_lines(int size)
{
    char **lines;

    if (size == 0)
        size = 1;
    lines = (char **)malloc(sizeof(char *) * (size + 1));
    if (!lines)
        print_error("Error: Unable to allocate memory for lines");
    return lines;
}

static void read_lines(const char *path, char **lines, int count)
{
    int fd;
    int i;
    char *line;
    int len;
    
    i = 0;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        print_error("Error: Unable to open .cub file");
    while ((line = get_next_line(fd)) != NULL)
    {
        len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        lines[i] = line;
        i++;
    }
    close(fd);
    if (count == 0)
    {
        lines[i] = ft_strdup("");
        i++;
    }
    lines[i] = NULL;
}

// Второй проход: выделить массив точного размера и заполнить
char **read_lines_from_path(const char *path)
{
    int count;
    char **lines;

    count = count_file_lines(path);
    lines = malloc_lines(count);
    read_lines(path, lines, count);
    return(lines);
}