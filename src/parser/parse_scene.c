/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:37:49 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/06 19:37:14 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include <fcntl.h>
#include <stdbool.h>
#include "../../libft/get_next_line.h"

static void ensure_cub_extension(const char *file_path)
{
    size_t len;
    
    if (!file_path)
        print_error("Error: Invalid file extension. Expected .cub");
    len = ft_strlen(file_path);
    if (len < 4 || ft_strncmp(file_path + len - 4, ".cub", 4) != 0)
        print_error("Error: Invalid file extension. Expected .cub");
}

// Проверки после карты и освобождение lines
static void post_map_and_final_checks(char **lines, t_scene *scene)
{
    free_split(lines);
    if (scene->screen_width <= 0 || scene->screen_height <= 0)
        print_error("Resolution not set or invalid");
    if (!scene->textures.north || !scene->textures.south ||
        !scene->textures.west || !scene->textures.east ||
        !scene->textures.sprite)
        print_error("One or more texture paths are missing");
    if (scene->colors.floor_color == -1 || scene->colors.ceiling_color == -1)
        print_error("Floor or ceiling color is missing");
    if (!scene->map.grid || scene->map.width <= 0 || scene->map.height <= 0)
        print_error("Map is missing or invalid");
}

// Правила после начала карты (запрещаем пустые строки и мусор)
static void enforce_map_block_rules(char **lines, int map_start)
{
    int k;
    int encountered_empty;

    k = map_start;
    encountered_empty = 0;
    while (lines[k])
    {
        if (lines[k][0] == '\0')
            encountered_empty = 1;
        else if (is_map_line(lines[k]))
        {
            if (encountered_empty)
            {
                free_split(lines);
                print_error("Empty line inside map");
            }
        }
        else
        {
            free_split(lines);
            print_error("Invalid content after map start");
        }
        k++;
    }
}

t_scene *parse_scene(const char *file_path, bool save_flag)
{
    t_scene *scene;
    char **lines;
    int map_start;

    ensure_cub_extension(file_path);
    scene = alloc_init_scene(save_flag);
    lines = read_lines_from_path(file_path);
    map_start = parse_header_until_map(lines, scene);
    enforce_map_block_rules(lines, map_start);
    parse_map(lines, map_start, scene);
    post_map_and_final_checks(lines, scene);
    return (scene);
}
