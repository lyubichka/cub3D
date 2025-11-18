/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:12:41 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/16 19:09:33 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void apply_color(char kind, int rgb[3], t_scene *scene)
{
    if (kind == 'F')
    {
        if (scene->colors.floor_color != -1)
            print_error("Duplicate floor color (F)");
        scene->colors.floor[0] = rgb[0];
        scene->colors.floor[1] = rgb[1];
        scene->colors.floor[2] = rgb[2];
        scene->colors.floor_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
        return ;
    }
    if (kind == 'C')
    {
        if (scene->colors.ceiling_color != -1)
            print_error("Duplicate ceiling color (C)");
        scene->colors.ceiling[0] = rgb[0];
        scene->colors.ceiling[1] = rgb[1];
        scene->colors.ceiling[2] = rgb[2];
        scene->colors.ceiling_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
        return ;
    }
    print_error("Unknown color identifier");
}

static void parse_color_line(char *line, t_scene *scene)
{
    char  **comma;
    int     rgb[3];

    comma = ft_split(line, ',');
    if (!comma)
        print_error("Memory error while parsing color");
    if (!comma[0] || !comma[1] || !comma[2] || comma[3] != NULL)
    {
        free_split(comma);
        print_error("Invalid color format (expected r,g,b)");
    }
    parse_rgb(comma, rgb);
    apply_color(line[0], rgb, scene);
}

void    parse_color(char *line, t_scene *scene)
{
    char    **parts;

    if (!line || !scene)
        print_error("parse_color: invalid arguments");
    if (!(line[0] == 'F' || line[0] == 'C'))
        print_error("Color line must start with F or C");
    parts = ft_split(line, ' ');
    if (!parts)
        print_error("Memory error while parsing color");
    if (!parts[0] || !parts[1] || parts[2] != NULL)
    {
        free_split(parts);
        print_error("Invalid color line (expected: F r,g,b)");
    }
    parse_color_line(parts[1], scene);
    free_split(parts);
}