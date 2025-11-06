/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:18:11 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/02 15:10:17 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*
 * Проверка, существует ли файл (и можно ли открыть на чтение)
 есть ли др функции кот могут это сделать
 */
static void	check_file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error("Texture file not found or cannot be opened");
	close(fd);
}

/*
 * Основная функция парсинга текстурной строки
 */
void	parse_texture(char *line, t_scene *scene)
{
    int i = 0;
    int start;
    char id[3] = {0,0,0};
    char *path;

    if (!line || !scene)
        print_error("parse_texture: invalid arguments");

    // Пропускаем ведущие пробелы/табуляции
    while (line[i] == ' ' || line[i] == '\t') i++;
    // Считываем 1-2 символа идентификатора
    start = i;
    while (line[i] && line[i] != ' ' && line[i] != '\t') 
        i++;
    if (i - start < 1 || i - start > 2)
        print_error("Invalid texture identifier length");
    id[0] = line[start];
    id[1] = (i - start == 2) ? line[start+1] : '\0';
    // Пропускаем промежуточные пробелы/табуляции
    while (line[i] == ' ' || line[i] == '\t') i++;
    if (!line[i])
        print_error("Texture path is missing");
    // Путь начинается здесь
    path = ft_strdup(line + i);
    if (!path)
        print_error("Memory error in parse_texture");
    // Обрежем завершающие пробелы/табуляции
    char *trimmed = ft_strtrim(path, " \t");
    free(path);
    if (!trimmed || trimmed[0] == '\0')
    {
        if (trimmed) free(trimmed);
        print_error("Texture path is empty");
    }
    // Убедимся, что после пути нет лишнего мусора (мы уже обрезали хвосты)
    // Проверяем, что в исходной строке не было символов до конца кроме пробелов/табов
    // так как trimmed убрал только хвост — этого достаточно.

    // Проверяем, что путь существует
    check_file_exists(trimmed);
    // Записываем путь в нужное поле
    if (ft_strncmp(id, "NO", 3) == 0)
    {
        if (scene->textures.north)
            print_error("Duplicate texture NO");
        scene->textures.north = ft_strdup(trimmed);
    }
    else if (ft_strncmp(id, "SO", 3) == 0)
    {
        if (scene->textures.south)
            print_error("Duplicate texture SO");
        scene->textures.south = ft_strdup(trimmed);
    }
    else if (ft_strncmp(id, "WE", 3) == 0)
    {
        if (scene->textures.west)
            print_error("Duplicate texture WE");
        scene->textures.west = ft_strdup(trimmed);
    }
    else if (ft_strncmp(id, "EA", 3) == 0)
    {
        if (scene->textures.east)
            print_error("Duplicate texture EA");
        scene->textures.east = ft_strdup(trimmed);
    }
    else if (ft_strncmp(id, "S", 2) == 0)
    {
        if (scene->textures.sprite)
            print_error("Duplicate texture S");
        scene->textures.sprite = ft_strdup(trimmed);
    }
    else
    {
        free(trimmed);
        print_error("Unknown texture identifier");
    }
    free(trimmed);
}
