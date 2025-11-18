/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:18:11 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/18 20:58:04 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include <fcntl.h>

static void read_identifier(char *line, int *i, char id[3])
{
    int start;
    int len;

    start = *i;
    while (line[*i] && line[*i] != ' ' && line[*i] != '\t')
        (*i)++;
    len = *i - start;
    if (len < 1 || len > 2)
        print_error("Invalid texture identifier length");
    id[0] = line[start];
    if (len == 2)
        id[1] = line[start + 1];
    else
        id[1] = '\0';
    id[2] = '\0';
}

static char *dup_trim_path_or_fail(char *line, int i)
{
    char *path;
    char *trimmed;

    if (!line[i])
        print_error("Texture path is missing");
    path = ft_strdup(line + i);
    if (!path)
        print_error("Memory error in parse_texture");
    trimmed = ft_strtrim(path, " \t");
    free(path);
    if (!trimmed || trimmed[0] == '\0')
    {
        if (trimmed)
            free(trimmed);
        print_error("Texture path is empty");
    }
    return (trimmed);
}

static void set_texture_path(char **target, const char *dup_msg,
    char *trimmed)
{
    if (*target)
    {
        free(trimmed);
        print_error(dup_msg);
    }
    *target = ft_strdup(trimmed);
    if (!*target)
    {
        free(trimmed);
        print_error("Memory error while duplicating texture path");
    }
}

static void assign_texture_by_id(t_scene *scene, const char *id,
    char *trimmed)
{
    if (ft_strncmp(id, "NO", 3) == 0)
        set_texture_path(&scene->textures.north,
            "Duplicate texture NO", trimmed);
    else if (ft_strncmp(id, "SO", 3) == 0)
        set_texture_path(&scene->textures.south,
            "Duplicate texture SO", trimmed);
    else if (ft_strncmp(id, "WE", 3) == 0)
        set_texture_path(&scene->textures.west,
            "Duplicate texture WE", trimmed);
    else if (ft_strncmp(id, "EA", 3) == 0)
        set_texture_path(&scene->textures.east,
            "Duplicate texture EA", trimmed);
    else if (ft_strncmp(id, "S", 2) == 0)
        set_texture_path(&scene->textures.sprite,
            "Duplicate texture S", trimmed);
    else
    {
        free(trimmed);
        print_error("Unknown texture identifier");
    }
}

void	parse_texture(char *line, t_scene *scene)
{
    int  i;
    int  fd;
    char id[3];
    char *trimmed;

    if (!line || !scene)
        print_error("parse_texture: invalid arguments");
    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    read_identifier(line, &i, id);
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    trimmed = dup_trim_path_or_fail(line, i);
    fd = open(trimmed, O_RDONLY);
    if (fd < 0)
    {
        free(trimmed);
        print_error("Texture file not found or cannot be opened");
    }
    close(fd);
    assign_texture_by_id(scene, id, trimmed);
    free(trimmed);
}
