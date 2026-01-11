/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:37:49 by veronikalub       #+#    #+#             */
/*   Updated: 2026/01/11 20:09:59 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Проверки после карты и освобождение lines
static void	post_map_and_final_checks(char **lines, t_scene *scene)
{
	free_split(lines);
	if (!scene->textures.north || !scene->textures.south
		|| !scene->textures.west || !scene->textures.east)
	{
		free_full_scene(scene);
		print_error_ctx("One or more mandatory textures are missing", NULL,
			NULL);
	}
	if (scene->colors.floor_color == -1 || scene->colors.ceiling_color == -1)
	{
		free_full_scene(scene);
		print_error_ctx("Floor or ceiling color is missing", NULL, NULL);
	}
	if (!scene->map.grid || scene->map.width <= 0 || scene->map.height <= 0)
	{
		free_full_scene(scene);
		print_error_ctx("Map is missing or invalid", NULL, NULL);
	}
}

// Правила после начала карты (запрещаем пустые строки и мусор)
static void	check_map_line_validity(char **lines, t_scene *scene,
	int encountered_empty, char *line)
{
	if (is_map_line(line))
	{
		if (encountered_empty)
		{
			free_split(lines);
			free_full_scene(scene);
			print_error_ctx("Empty line inside map", NULL, NULL);
		}
	}
	else
	{
		free_split(lines);
		free_full_scene(scene);
		print_error_ctx("Invalid content after map start", NULL, NULL);
	}
}

static void	enforce_map_block_rules(char **lines, int map_start, t_scene *scene)
{
	int	k;
	int	encountered_empty;

	k = map_start;
	encountered_empty = 0;
	while (lines[k])
	{
		if (lines[k][0] == '\0')
			encountered_empty = 1;
		else
			check_map_line_validity(lines, scene, encountered_empty, lines[k]);
		k++;
	}
}

t_scene	*parse_scene(const char *file_path, bool save_flag)
{
	t_scene	*scene;
	char	**lines;
	int		map_start;

	validate_file_path(file_path);
	scene = init_scene(save_flag);
	lines = read_lines_from_path(file_path);
	map_start = parse_header_until_map(lines, scene);
	if (map_start < 0)
	{
		free_split(lines);
		free_full_scene(scene);
		print_error_ctx("No map found in .cub file", NULL, NULL);
	}
	enforce_map_block_rules(lines, map_start, scene);
	parse_map(lines, map_start, scene);
	post_map_and_final_checks(lines, scene);
	return (scene);
}
