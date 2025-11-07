/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:14:30 by veronikalub       #+#    #+#             */
/*   Updated: 2025/10/30 14:43:53 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	is_number_str(const char *s)
{
    int i;

    if (!s || !*s)
        return (0);
    i = 0;
    while (s[i])
    {
        if (!(s[i] >= '0' && s[i] <= '9'))
            return (0);
        i++;
    }
    return (1);
}

void	parse_resolution(char *line, t_scene *scene)
{
	char	**parts;
	int		w;
	int		h;

	if (!line || !scene)
		print_error("parse_resolution: invalid arguments");

	// Не позволим дубль R
	if (scene->screen_width != 0 || scene->screen_height != 0)
		print_error("Resolution is specified multiple times");

	// Разделим строку по пробелам
	parts = ft_split(line, ' ');
	if (!parts)
		print_error("Memory error while parsing resolution");

	// Ожидаем: parts[0] == "R", parts[1] == width, parts[2] == height, parts[3] == NULL
	if (!parts[0] || ft_strncmp(parts[0], "R", 2) != 0 || !parts[1] || !parts[2] || parts[3] != NULL)
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

	w = ft_atoi(parts[1]);
	h = ft_atoi(parts[2]);

	if (w <= 0 || h <= 0)
	{
		free_split(parts);
		print_error("Resolution must be greater than 0");
	}

	// Дополнительная защита: если кто-то указал очень большие числа,
	// можно ограничить их разумными максимальными значениями.
	// Здесь я не накладываю жёстких лимитов — если нужно, добавим позже.
	scene->screen_width = w;
	scene->screen_height = h;

	free_split(parts);
}
