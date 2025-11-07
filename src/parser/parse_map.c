/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:59:42 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/01 01:04:19 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*
 * Проверяет, допустим ли символ
 */
static bool	is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || 
            c == 'E' || c == 'W' || c == ' ');
}

/*
 * Считает количество строк карты
 */
static int	count_map_lines(char **lines, int start)
{
	int	i = start;

	while (lines[i] && lines[i][0] != '\0')
		i++;
	return (i - start);
}

/*
 * Проверяет, что карта прямоугольная (все строки одной длины)
 */
static int	get_max_width(char **lines, int start, int end)
{
	int	max = 0;
	int	len;

	while (start < end)
	{
		len = ft_strlen(lines[start]);
		if (len > max)
			max = len;
		start++;
	}
	return (max);
}

/*
 * Проверка, что карта замкнута стенами (очень простая версия)
 */
static char    get_at(t_scene *scene, int y, int x)
{
    if (y < 0 || y >= scene->map.height || x < 0 || x >= scene->map.width)
        return (' ');
    return (scene->map.grid[y][x]);
}

static int is_player(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	check_map_closed(t_scene *scene)
{
    int y;
    int x;

    // Верхняя и нижняя границы не должны содержать пола/игрока
    x = 0;
    while (x < scene->map.width)
    {
        char t = get_at(scene, 0, x);
        char b = get_at(scene, scene->map.height - 1, x);
        if (t == '0' || is_player(t) || b == '0' || is_player(b))
            print_error("Map not closed at top/bottom border");
        x++;
    }
    // Левая и правая границы
    y = 0;
    while (y < scene->map.height)
    {
        char l = get_at(scene, y, 0);
        char r = get_at(scene, y, scene->map.width - 1);
        if (l == '0' || is_player(l) || r == '0' || is_player(r))
            print_error("Map not closed at left/right border");
        y++;
    }
    // Внутренние клетки: у пола/игрока не должно быть соседей-пробелов
    y = 0;
    while (y < scene->map.height)
    {
        x = 0;
        while (x < scene->map.width)
        {
            char c = get_at(scene, y, x);
            if (c == '0' || is_player(c))
            {
                if (get_at(scene, y - 1, x) == ' ' ||
                    get_at(scene, y + 1, x) == ' ' ||
                    get_at(scene, y, x - 1) == ' ' ||
                    get_at(scene, y, x + 1) == ' ')
                    print_error("Map has open space adjacent to floor/player");
            }
            x++;
        }
        y++;
    }
}

/*
 * Главная функция парсинга карты
 */
void	parse_map(char **lines, int start_line, t_scene *scene)
{
    int	map_lines;
    int	max_width;
    int	i;
    int	player_found = 0;

	map_lines = count_map_lines(lines, start_line);
    if (map_lines <= 0)
        print_error("No map found in .cub file");
    if (map_lines > MAX_MAP_HEIGHT)
        print_error("Map height exceeds MAX_MAP_HEIGHT");
    scene->map.grid = malloc(sizeof(char *) * (map_lines + 1));
    if (!scene->map.grid)
        print_error("Memory allocation failed for map");
    max_width = get_max_width(lines, start_line, start_line + map_lines);
    if (max_width > MAX_MAP_WIDTH)
        print_error("Map width exceeds MAX_MAP_WIDTH");
    i = 0;
    while (i < map_lines)
    {
        int src_len = ft_strlen(lines[start_line + i]);
        int j;
        scene->map.grid[i] = (char *)malloc(max_width + 1);
        if (!scene->map.grid[i])
            print_error("Map line allocation failed");
        // Копируем исходную строку и дополняем пробелами до прямоугольника
        j = 0;
        while (j < src_len)
        {
            scene->map.grid[i][j] = lines[start_line + i][j];
            j++;
        }
        while (j < max_width)
            scene->map.grid[i][j++] = ' ';
        scene->map.grid[i][max_width] = '\0';
        // Проверка символов и поиск игрока
            int k = 0;
            while (k < max_width)
            {
                char c = scene->map.grid[i][k];
                if (!is_valid_map_char(c))
                    print_error("Invalid character in map");
                if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                {
                    if (player_found)
                        print_error("Multiple player positions found");
                    player_found = 1;
                    scene->map.player_x = k;
                    scene->map.player_y = i;
                    scene->map.player_dir = c;
                }
                k++;
            }
        i++;
    }
    scene->map.grid[i] = NULL;

    scene->map.height = map_lines;
    scene->map.width = max_width;

    if (!player_found)
        print_error("No player start position found");

    check_map_closed(scene);
}
