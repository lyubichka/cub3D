/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header_till_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:21:38 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/08 17:29:47 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Проверка: строка состоит только из допустимых символов карты (' ', '0', '1', 'N', 'S', 'E', 'W')
static int is_map_line(const char *s)
{
    int i = 0;
    if (!s)
        return 0;
    // Пустая строка не является строкой карты
    if (s[0] == '\0')
        return 0;
    while (s[i])
    {
        char c = s[i];
        if (!(c == ' ' || c == '0' || c == '1' ||
              c == 'N' || c == 'S' || c == 'E' || c == 'W'))
            return 0;
        i++;
    }
    return 1;
}

static int parse_header_until_map(char **lines, t_scene *scene)
{
    int i = 0;
    int map_start = -1;
    bool seen_r = false, seen_no = false, seen_so = false;
    bool seen_we = false, seen_ea = false, seen_s = false;
    bool seen_f = false, seen_c = false;
    while (lines[i])
    {
        char *trim = ft_strtrim(lines[i], " \t");
        if (!trim) { free_split(lines); print_error("alloc fail"); }
        if (trim[0] == '\0')
        {
            free(trim);
            i++;
            continue;
        }
        if (is_map_line(lines[i]))
        {
            free(trim);
            map_start = i;
            break;
        }
        handle_header_trim(trim, lines, scene, &seen_r, &seen_no, &seen_so, &seen_we, &seen_ea, &seen_s, &seen_f, &seen_c);
        free(trim);
        i++;
    }
    if (map_start == -1) { free_split(lines); print_error("Map section not found"); }
    if (!seen_r || !seen_no || !seen_so || !seen_we || !seen_ea || !seen_s || !seen_f || !seen_c)
    { free_split(lines); print_error("Missing one or more directives before map"); }
    return (map_start);
}