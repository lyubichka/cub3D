/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:14:30 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/16 15:39:30 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static char **split_parts_or_fail(char *line)
{
    char **parts;

    parts = ft_split(line, ' ');
    if (!parts)
        print_error("Memory error while parsing resolution");
    return (parts);
}

static void parse_and_apply(char **parts, t_scene *scene)
{
    int w;
    int h;

    w = ft_atoi(parts[1]);
    h = ft_atoi(parts[2]);
    if (w <= 0 || h <= 0)
    {
        free_split(parts);
        print_error("Resolution must be greater than 0");
    }
    scene->screen_width = w;
    scene->screen_height = h;
    free_split(parts);
}

void	parse_resolution(char *line, t_scene *scene)
{
    char	**parts;

    if (!line || !scene)
        print_error("parse_resolution: invalid arguments");
    parts = split_parts_or_fail(line);
    // Ожидаем: parts[0] == "R", parts[1] == width, parts[2] == height, parts[3] == NULL
    if (!parts[0] || ft_strncmp(parts[0], "R", 2) != 0
        || !parts[1] || !parts[2] || parts[3] != NULL)
    {
        free_split(parts);
        print_error("Invalid resolution line (expected: R <width> <height>)");
    }
    // Проверяем, что это положительные целые числа (без лишних символов)
    if (!is_number_str(parts[1]) || !is_number_str(parts[2]))
    {
        free_split(parts);
        print_error("Resolution values must be positive integers");
    }
    // Дополнительная защита: если кто-то указал очень большие числа,
    // можно ограничить их разумными максимальными значениями.
    // Здесь я не накладываю жёстких лимитов — если нужно, добавим позже.
    parse_and_apply(parts, scene);
}
