/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:14:30 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/26 02:43:48 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static char	**split_parts_or_fail(char *line)
{
	char	**parts;

	parts = ft_split(line, ' ');
	if (!parts)
		print_error("Memory error while parsing resolution");
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
		print_error("Resolution must be greater than 0");
	}
	scene->screen_width = w;
	scene->screen_height = h;
	free_split(parts);
}

void	parse_resolution(char *line, t_scene *scene)
{
	char	**parts;

	if (!line || !scene)
		print_error("parse_resolution: invalid arguments");
	parts = split_parts_or_fail(line);
	if (!parts[0] || ft_strncmp(parts[0], "R", 2) != 0
		|| !parts[1] || !parts[2] || parts[3] != NULL)
	{
		free_split(parts);
		print_error("Invalid resolution line (expected: R <width> <height>)");
	}
	if (!is_number_str(parts[1]) || !is_number_str(parts[2]))
	{
		free_split(parts);
		print_error("Resolution values must be positive integers");
	}
	parse_and_apply(parts, scene);
}
