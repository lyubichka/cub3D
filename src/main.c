/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:20:08 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/06 19:26:13 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// Mock function to create a sample scene for testing
t_scene *create_test_scene(void)
{
    t_scene *scene = malloc(sizeof(t_scene));
    if (!scene)
        return NULL;

    scene->screen_width = 800;
    scene->screen_height = 600;

    // colors
    scene->colors.floor_color = 0x777777;
    scene->colors.ceiling_color = 0x87CEEB;

    // fake textures (you’ll load them later)
    scene->textures.north = "./textures/north.xpm";
    scene->textures.south = "./textures/south.xpm";
    scene->textures.east  = "./textures/east.xpm";
    scene->textures.west  = "./textures/west.xpm";

    // small hardcoded map
    static char *map_data[] = {
        "111111",
        "100001",
        "1000N1",
        "111111",
        NULL
    };
    scene->map.grid = map_data;
    scene->map.width = 6;
    scene->map.height = 4;
    scene->map.player_x = 3;
    scene->map.player_y = 2;
    scene->map.player_dir = 'N';

    scene->save_bmp = 0;
    return scene;
}

int	main(void)
{
	t_scene	*scene = create_test_scene();

    init_player(scene);

	// init mlx
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, scene->screen_width, scene->screen_height, "Cub3D");
    // void    *img = mlx_new_image(mlx, scene->screen_width, scene->screen_height);

	// call your render function
	render_scene(scene, mlx, win);

	mlx_loop(mlx);
	return (0);
}

