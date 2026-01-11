/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:14:30 by veronikalub       #+#    #+#             */
/*   Updated: 2026/01/11 20:06:07 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static char	**split_parts_or_fail(char *line)
{
	char	**parts;

	parts = ft_split(line, ' ');
	if (!parts)
		print_error_ctx("Memory error while parsing resolution", NULL, NULL);
	return (parts);
}

static void	parse_and_apply(char **parts, t_scene *scene)
{
	int	w;
	int	h;

	w = ft_atoi(parts[1]);
	h = ft_atoi(parts[2]);
	if (w <= 0 || h <= 0)
	{
		free_split(parts);
		print_error_ctx("Resolution must be greater than 0", NULL, NULL);
	}
	if (w > 1920)
		w = 1920;
	if (h > 1080)
		h = 1080;
	scene->screen_width = w;
	scene->screen_height = h;
	free_split(parts);
}

void	parse_resolution(char *line, t_scene *scene)
{
	char	**parts;

	if (!line || !scene)
		print_error_ctx("parse_resolution: invalid arguments", NULL, NULL);
	parts = split_parts_or_fail(line);
	if (!parts[0] || ft_strncmp(parts[0], "R", 2) != 0
		|| !parts[1] || !parts[2] || parts[3] != NULL)
	{
		free_split(parts);
		print_error_ctx("Invalid resolution line (expected: R <w> <h>)", NULL,
			NULL);
	}
	if (!is_number_str(parts[1]) || !is_number_str(parts[2]))
	{
		free_split(parts);
		print_error_ctx("Resolution values must be positive integers", NULL,
			NULL);
	}
	parse_and_apply(parts, scene);
}
