/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:16:19 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/08 17:30:09 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Первый проход: посчитать строки в файле
static int count_file_lines(const char *path)
{
    int fd; int n = 0; char *line;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        print_error("Error: Unable to open .cub file");
    while ((line = get_next_line(fd)) != NULL)
    {
        free(line);
        n++;
    }
    close(fd);
    return (n);
}

// Второй проход: выделить массив точного размера и заполнить
static char **read_lines_from_path(const char *path)
{
    int i = 0;
    int count;
    int size;

    count = count_file_lines(path);
    if (count > 0)
        size = count;
    else
        size = 1;
    char **lines = (char **)malloc(sizeof(char *) * (size + 1));
    int fd; char *line; int len;
    if (!lines)
        print_error("alloc fail");
    fd = open(path, O_RDONLY);
    if (fd < 0)
        print_error("Error: Unable to open .cub file");
    while ((line = get_next_line(fd)) != NULL)
    {
        len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        lines[i++] = line;
    }
    close(fd);
    if (count == 0)
        lines[i++] = ft_strdup("");
    lines[i] = NULL;
    return (lines);
}