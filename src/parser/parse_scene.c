/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:37:49 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/19 12:35:12 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void init_scene_defaults(t_scene *scene)
{
    scene->screen_width = 800;
    scene->screen_height = 600;
    scene->textures.north = NULL;
    scene->textures.south = NULL;
    scene->textures.west = NULL;
    scene->textures.east = NULL;
    scene->textures.sprite = NULL;
    scene->colors.floor[0] = 0;
    scene->colors.floor[1] = 0;
    scene->colors.floor[2] = 0;
    scene->colors.ceiling[0] = 0;
    scene->colors.ceiling[1] = 0;
    scene->colors.ceiling[2] = 0;
    scene->colors.floor_color = -1;
    scene->colors.ceiling_color = -1;
    scene->map.grid = NULL;
    scene->map.width = 0;
    scene->map.height = 0;
    scene->map.player_x = 0;
    scene->map.player_y = 0;
    scene->map.player_dir = 'N';
}

t_scene *init_scene(bool save_flag)
{
    t_scene *scene;

    scene = (t_scene *)ft_calloc(1, sizeof(t_scene));
    if (!scene)
        print_error("Error: Memory allocation failed for t_scene");
    if (save_flag)
        scene->save_bmp = 1;
    else
        scene->save_bmp = 0;
    init_scene_defaults(scene);
    return (scene);
}

// Проверки после карты и освобождение lines
static void post_map_and_final_checks(char **lines, t_scene *scene)
{
    free_split(lines);
    if (!scene->textures.north || !scene->textures.south ||
        !scene->textures.west || !scene->textures.east)
        print_error("One or more mandatory textures are missing");
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
    char    **lines;
    int     map_start;
    size_t  len;

    if (!file_path)
        print_error("Error: Invalid file extension. Expected .cub");
    len = ft_strlen(file_path);
    if (len < 4 || ft_strncmp(file_path + len - 4, ".cub", 4) != 0)
        print_error("Error: Invalid file extension. Expected .cub");
    scene = init_scene(save_flag);
    lines = read_lines_from_path(file_path);
    map_start = parse_header_until_map(lines, scene);
    enforce_map_block_rules(lines, map_start);
    parse_map(lines, map_start, scene);
    post_map_and_final_checks(lines, scene);
    return (scene);
}
