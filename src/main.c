/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/10/28 12:16:35 by veronikalub       #+#    #+#             */
/*   Updated: 2025/10/30 14:40:26 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	check_arguments(int argc, char **argv, bool *save_flag)
{
	*save_flag = false;
	if (argc < 2 || argc > 3)
		print_error_ctx("wrong number of arguments", NULL, NULL);
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 6) == 0)
			*save_flag = true;
		else
			print_error_ctx("Second argument must be '--save' if present", NULL,
				NULL);
	}
}

static void	handle_save_mode(t_scene *scene)
{
	if (save_mode_render_and_write(scene, "output.bmp") != 0)
	{
		free_full_scene(scene);
		print_error_ctx("Failed to save BMP file", NULL, NULL);
	}
	free_full_scene(scene);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;
	bool	save_flag;

	check_arguments(argc, argv, &save_flag);
	scene = parse_scene(argv[1], save_flag);
	if (!scene)
		print_error_ctx("failed to parse scene", NULL, NULL);
	if (save_flag)
	{
		handle_save_mode(scene);
		return (0);
	}
	else
		run_engine(scene);
	return (0);
}
