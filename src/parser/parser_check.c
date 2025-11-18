/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:33:27 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/18 20:13:53 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static char    get_at(t_scene *scene, int y, int x)
{
    if (y < 0 || y >= scene->map.height || x < 0 || x >= scene->map.width)
        return (' ');
    return (scene->map.grid[y][x]);
}

static void check_adjacent_spaces(t_scene *scene, int y, int x)
{
    if (get_at(scene, y - 1, x) == ' ')
        print_error("Map has open space adjacent to floor/player");
    if (get_at(scene, y + 1, x) == ' ')
        print_error("Map has open space adjacent to floor/player");
    if (get_at(scene, y, x - 1) == ' ')
        print_error("Map has open space adjacent to floor/player");
    if (get_at(scene, y, x + 1) == ' ')
        print_error("Map has open space adjacent to floor/player");
}

void check_interior_cells(t_scene *scene)
{
    int y;
    int x;
    char c;

    y = 0;
    while (y < scene->map.height)
    {
        x = 0;
        while (x < scene->map.width)
        {
            c = get_at(scene, y, x);
            if (c == '0' || is_player(c))
                check_adjacent_spaces(scene, y, x);
            x++;
        }
        y++;
    }
}

void check_top_bottom_borders(t_scene *scene)
{
    int x;
    x = 0;
    while (x < scene->map.width)
    {
        char t;
        char b;

        t = get_at(scene, 0, x);
        b = get_at(scene, scene->map.height - 1, x);
        if (t == '0' || is_player(t) || b == '0' || is_player(b))
            print_error("Map not closed at top/bottom border");
        x++;
    }
}

void check_left_right_borders(t_scene *scene)
{
    int y;
    char l;
    char r;

    y = 0;
    while (y < scene->map.height)
    {
        l = get_at(scene, y, 0);
        r = get_at(scene, y, scene->map.width - 1);
        if (l == '0' || is_player(l) || r == '0' || is_player(r))
            print_error("Map not closed at left/right border");
        y++;
    }
}
