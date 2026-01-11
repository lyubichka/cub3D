/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:12:41 by veronikalub       #+#    #+#             */
/*   Updated: 2026/01/11 19:46:05 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	apply_color(char kind, int rgb[3], t_scene *scene)
{
	if (kind == 'F')
	{
		if (scene->colors.floor_color != -1)
			print_error_ctx("Duplicate floor color (F)", NULL, NULL);
		scene->colors.floor[0] = rgb[0];
		scene->colors.floor[1] = rgb[1];
		scene->colors.floor[2] = rgb[2];
		scene->colors.floor_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
		return ;
	}
	if (kind == 'C')
	{
		if (scene->colors.ceiling_color != -1)
			print_error_ctx("Duplicate ceiling color (C)", NULL, NULL);
		scene->colors.ceiling[0] = rgb[0];
		scene->colors.ceiling[1] = rgb[1];
		scene->colors.ceiling[2] = rgb[2];
		scene->colors.ceiling_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
		return ;
	}
	print_error_ctx("Unknown color identifier", NULL, NULL);
}

static void	parse_color_line(char *line, char kind, t_hdr_ctx *ctx,
		char **outer_parts)
{
	char	**comma;
	int		rgb[3];
	int		count;

	comma = ft_split(line, ',');
	if (!comma)
		print_error_ctx("Memory error while parsing color", NULL, NULL);
	count = 0;
	while (comma[count])
		count++;
	if (count != 3)
	{
		free_split(comma);
		print_error_ctx("Invalid color format (expected r,g,b)", NULL, NULL);
	}
	parse_rgb(comma, rgb, ctx, outer_parts);
	apply_color(kind, rgb, ctx->scene);
}

void	parse_color(char *line, t_hdr_ctx *ctx)
{
	char	**parts;
	char	kind;

	if (!line || !ctx || !ctx->scene)
		print_error_ctx("parse_color: invalid arguments", NULL, NULL);
	if (!(line[0] == 'F' || line[0] == 'C'))
		print_error_ctx("Color line must start with F or C", NULL, NULL);
	kind = line[0];
	parts = ft_split(line, ' ');
	if (!parts)
		print_error_ctx("Memory error while parsing color", NULL, NULL);
	if (!parts[0] || !parts[1] || parts[2] != NULL)
	{
		free_split(parts);
		print_error_ctx("Invalid color line (expected: F r,g,b)", NULL, NULL);
	}
	parse_color_line(parts[1], kind, ctx, parts);
	free_split(parts);
}
