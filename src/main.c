/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 12:16:35 by veronikalub       #+#    #+#             */
/*   Updated: 2025/10/30 14:40:26 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int main(int argc, char **argv)
{
	t_scene *scene;
	bool save_flag;

	save_flag = false;
	if (argc < 2 || argc > 3)
	{
		write(2, "Error\nwrong number of arguments\n", 33);
		exit(1);
	}
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 6) == 0)
			save_flag = true;
		else
			print_error("Second argument must be '--save' if present");
	}
	scene = parse_scene(argv[1], save_flag);
	init_player(scene);          /* set player.pos/dir/plane based on map.player_* */
	/* если указан --save, рендерим один кадр в offscreen-изображение и пишем BMP */
	if (save_flag)
	{
		if (save_mode_render_and_write(scene, "screenshot.bmp") != 0)
			print_error("Failed to save BMP");
		free_scene(scene);
		return (0);
	}
	/* обычный режим: запускаем графический движок с окном */
	run_engine(scene);
	free_scene(scene);
	return (0);
}
