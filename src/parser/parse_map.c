/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:59:42 by veronikalub       #+#    #+#             */
/*   Updated: 2026/01/11 19:46:05 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	validate_map_line(t_map_build_ctx *ctx, int i)
{
	int		k;
	char	c;

	k = 0;
	while (k < ctx->max_width)
	{
		c = ctx->scene->map.grid[i][k];
		if (!(c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
				|| c == 'W' || c == ' '))
			print_error_ctx("Invalid character in map", NULL, NULL);
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			if (ctx->player_found)
				print_error_ctx("Multiple player positions found", NULL, NULL);
			ctx->player_found = 1;
			ctx->scene->map.player_x = k;
			ctx->scene->map.player_y = i;
			ctx->scene->map.player_dir = c;
		}
		k++;
	}
}

static void	build_map_line(t_map_build_ctx *ctx, int i, t_scene *scene)
{
	int	src_len;
	int	j;

	src_len = ft_strlen(ctx->lines[ctx->start_line + i]);
	scene->map.grid[i] = (char *)malloc(ctx->max_width + 1);
	if (!scene->map.grid[i])
		print_error_ctx("Map line allocation failed", NULL, NULL);
	j = 0;
	while (j < src_len)
	{
		scene->map.grid[i][j] = ctx->lines[ctx->start_line + i][j];
		j++;
	}
	while (j < ctx->max_width)
	{
		scene->map.grid[i][j] = ' ';
		j++;
	}
	scene->map.grid[i][ctx->max_width] = '\0';
	validate_map_line(ctx, i);
}

static void	build_map(t_map_build_ctx *ctx, t_scene *scene)
{
	int	i;

	i = 0;
	while (i < ctx->map_lines)
	{
		build_map_line(ctx, i, scene);
		i++;
	}
	scene->map.grid[i] = NULL;
}

static void	preflight_map(t_map_build_ctx *ctx)
{
	int	start;
	int	i;

	start = ctx->start_line;
	i = start;
	while (ctx->lines[i] && ctx->lines[i][0] != '\0')
		i++;
	ctx->map_lines = i - start;
	if (ctx->map_lines <= 0)
		print_error_ctx("No map found in .cub file", NULL, NULL);
	if (ctx->map_lines > MAX_MAP_HEIGHT)
		print_error_ctx("Map height exceeds MAX_MAP_HEIGHT", NULL, NULL);
	ctx->scene->map.grid = malloc(sizeof(char *) * (ctx->map_lines + 1));
	if (!ctx->scene->map.grid)
		print_error_ctx("Memory allocation failed for map", NULL, NULL);
	ctx->max_width = get_max_width(ctx->lines, start, start + ctx->map_lines);
	if (ctx->max_width > MAX_MAP_WIDTH)
		print_error_ctx("Map width exceeds MAX_MAP_WIDTH", NULL, NULL);
}

void	parse_map(char **lines, int start_line, t_scene *scene)
{
	t_map_build_ctx	ctx;

	ctx.lines = lines;
	ctx.start_line = start_line;
	ctx.player_found = 0;
	ctx.scene = scene;
	preflight_map(&ctx);
	build_map(&ctx, scene);
	scene->map.height = ctx.map_lines;
	scene->map.width = ctx.max_width;
	if (!ctx.player_found)
		print_error_ctx("No player start position found", NULL, NULL);
	check_top_bottom_borders(scene);
	check_left_right_borders(scene);
	check_interior_cells(scene);
}
