/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:24:14 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/06 19:25:54 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Хелперы для компактной обработки заголовков
static void handle_texture(char *trim, char **lines, bool *seen,
                           const char *dup_msg, t_scene *scene)
{
    if (*seen)
    {
        free(trim);
        free_split(lines);
        print_error(dup_msg);
    }
    *seen = true;
    parse_texture(trim, scene);
}

static void handle_resolution(char *trim, char **lines, bool *seen,
                              t_scene *scene)
{
    if (*seen)
    {
        free(trim);
        free_split(lines);
        print_error("Duplicate R directive");
    }
    *seen = true;
    parse_resolution(trim, scene);
}

static void handle_color(char *trim, char **lines, bool *seen,
                         const char *dup_msg, t_scene *scene)
{
    if (*seen)
    {
        free(trim);
        free_split(lines);
        print_error(dup_msg);
    }
    *seen = true;
    parse_color(trim, scene);
}

// Проход по заголовку до начала карты, возвращает map_start и выставляет поля scene
static void handle_header_trim(char *trim, char **lines, t_scene *scene,
    bool *seen_r, bool *seen_no, bool *seen_so, bool *seen_we,
    bool *seen_ea, bool *seen_s, bool *seen_f, bool *seen_c)
{
    if (ft_strncmp(trim, "NO", 2) == 0)
        handle_texture(trim, lines, seen_no, "Duplicate NO directive", scene);
    else if (ft_strncmp(trim, "SO", 2) == 0)
        handle_texture(trim, lines, seen_so, "Duplicate SO directive", scene);
    else if (ft_strncmp(trim, "WE", 2) == 0)
        handle_texture(trim, lines, seen_we, "Duplicate WE directive", scene);
    else if (ft_strncmp(trim, "EA", 2) == 0)
        handle_texture(trim, lines, seen_ea, "Duplicate EA directive", scene);
    else if (ft_strncmp(trim, "S ", 2) == 0 || ft_strncmp(trim, "S\t", 2) == 0)
        handle_texture(trim, lines, seen_s, "Duplicate S directive", scene);
    else if (trim[0] == 'R')
        handle_resolution(trim, lines, seen_r, scene);
    else if (trim[0] == 'F')
        handle_color(trim, lines, seen_f, "Duplicate F directive", scene);
    else if (trim[0] == 'C')
        handle_color(trim, lines, seen_c, "Duplicate C directive", scene);
    else
    {
        free(trim);
        free_split(lines);
        print_error("Unknown identifier in header");
    }
}