/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:18:11 by veronikalub       #+#    #+#             */
/*   Updated: 2026/01/11 20:00:19 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include <fcntl.h>

static void	read_identifier(char *line, int *i, char id[3])
{
	int	start;
	int	len;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t')
		(*i)++;
	len = *i - start;
	if (len < 1 || len > 2)
		print_error_ctx("Invalid texture identifier length", NULL, NULL);
	id[0] = line[start];
	if (len == 2)
		id[1] = line[start + 1];
	else
		id[1] = '\0';
	id[2] = '\0';
}

static char	*dup_trim_path_or_fail(char *line, int i)
{
	char	*path;
	char	*trimmed;

	if (!line[i])
		print_error_ctx("Texture path is missing", NULL, NULL);
	path = ft_strdup(line + i);
	if (!path)
		print_error_ctx("Memory error in parse_texture", NULL, NULL);
	trimmed = ft_strtrim(path, " \t");
	free(path);
	if (!trimmed || trimmed[0] == '\0')
	{
		if (trimmed)
			free(trimmed);
		print_error_ctx("Texture path is empty", NULL, NULL);
	}
	return (trimmed);
}

static void	set_texture_path(char **target, const char *dup_msg, char *trimmed,
		t_hdr_ctx *ctx)
{
	if (*target)
	{
		free(trimmed);
		print_error_ctx(dup_msg, ctx, NULL);
	}
	*target = ft_strdup(trimmed);
	if (!*target)
	{
		free(trimmed);
		print_error_ctx("Memory error while duplicating texture path", ctx,
			NULL);
	}
}

static void	assign_texture_by_id(t_hdr_ctx *ctx, const char *id, char *trimmed)
{
	if (ft_strncmp(id, "NO", 3) == 0)
		set_texture_path(&ctx->scene->textures.north, "Duplicate texture NO",
			trimmed, ctx);
	else if (ft_strncmp(id, "SO", 3) == 0)
		set_texture_path(&ctx->scene->textures.south, "Duplicate texture SO",
			trimmed, ctx);
	else if (ft_strncmp(id, "WE", 3) == 0)
		set_texture_path(&ctx->scene->textures.west, "Duplicate texture WE",
			trimmed, ctx);
	else if (ft_strncmp(id, "EA", 3) == 0)
		set_texture_path(&ctx->scene->textures.east, "Duplicate texture EA",
			trimmed, ctx);
	else
	{
		free(trimmed);
		print_error_ctx("Unknown texture identifier", ctx, NULL);
	}
}

void	parse_texture(char *line, t_hdr_ctx *ctx)
{
	int		i;
	int		fd;
	char	id[3];
	char	*trimmed;

	if (!line || !ctx || !ctx->scene)
		print_error_ctx("parse_texture: invalid arguments", NULL, NULL);
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
		print_error_ctx("Texture file not found or cannot be opened", ctx,
			NULL);
	}
	close(fd);
	assign_texture_by_id(ctx, id, trimmed);
	free(trimmed);
}
