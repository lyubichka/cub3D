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

/*
 * create_rgb helper (in case your parser does not provide create_rgb_int)
 * If you already have create_rgb_int available from parser, you can replace
 * the inline formula with a call to it.
 */
static int make_rgb_int(int r, int g, int b)
{
	return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

/*
 * create_test_scene
 * Allocates and returns a pointer to a heap-allocated t_scene populated
 * with test values. Caller should free with free_test_scene().
 */
t_scene *create_test_scene(void)
{
	t_scene *scene;
	char **grid;

	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);

	/* screen */
	scene->screen_width = 800;
	scene->screen_height = 600;
	scene->save_bmp = 0;

	/* textures (make sure these files exist in ./textures/) */
	scene->textures.north = ft_strdup("./textures/north.xpm");
	scene->textures.south = ft_strdup("./textures/south.xpm");
	scene->textures.east  = ft_strdup("./textures/east.xpm");
	scene->textures.west  = ft_strdup("./textures/west.xpm");
	scene->textures.sprite = ft_strdup("./textures/sprite.xpm"); /* optional */

	/* colors (rgb arrays) */
	scene->colors.ceiling[0] = 135; /* light blue */
	scene->colors.ceiling[1] = 206;
	scene->colors.ceiling[2] = 235;
	scene->colors.floor[0] = 48;    /* dark gray */
	scene->colors.floor[1] = 48;
	scene->colors.floor[2] = 48;

	/* packed colors */
	scene->colors.ceiling_color = make_rgb_int(
		scene->colors.ceiling[0],
		scene->colors.ceiling[1],
		scene->colors.ceiling[2]
	);
	scene->colors.floor_color = make_rgb_int(
		scene->colors.floor[0],
		scene->colors.floor[1],
		scene->colors.floor[2]
	);

	/* simple map (height x width):
	   1 = wall, 0 = empty, N = player starting pos facing North
	*/
	scene->map.height = 6;
	scene->map.width = 8;

	grid = (char **)malloc((scene->map.height + 1) * sizeof(char *));
	if (!grid)
	{
		free(scene);
		return (NULL);
	}

	grid[0] = ft_strdup("11111111");
	grid[1] = ft_strdup("1N000001");
	grid[2] = ft_strdup("10000001");
	grid[3] = ft_strdup("10001001");
	grid[4] = ft_strdup("10000001");
	grid[5] = ft_strdup("11111111");
	grid[6] = NULL;

	scene->map.grid = grid;

	/* player info (tile coordinates and facing direction) */
	/* For the map above, 'N' is at (x = 2, y = 2)  (0-based) */
	scene->map.player_x = 1;
	scene->map.player_y = 1;
	scene->map.player_dir = 'N';

	/* player struct will be initialized by init_player() later */
	scene->player.pos_x = 0.0;
	scene->player.pos_y = 0.0;
	scene->player.dir_x = 0.0;
	scene->player.dir_y = 0.0;
	scene->player.plane_x = 0.0;
	scene->player.plane_y = 0.0;

	return (scene);
}

/*
 * free_test_scene
 * Frees memory allocated by create_test_scene()
 */
void free_test_scene(t_scene *scene)
{
	int i;

	if (!scene)
		return;

	if (scene->textures.north)
		free(scene->textures.north);
	if (scene->textures.south)
		free(scene->textures.south);
	if (scene->textures.east)
		free(scene->textures.east);
	if (scene->textures.west)
		free(scene->textures.west);
	if (scene->textures.sprite)
		free(scene->textures.sprite);

	if (scene->map.grid)
	{
		i = 0;
		while (i < scene->map.height && scene->map.grid[i] != NULL)
		{
			free(scene->map.grid[i]);
			i++;
		}
		free(scene->map.grid);
	}

	free(scene);
}

int main(int argc, char **argv)
{
	t_scene *scene;

	(void)argc;
	(void)argv;

	scene = create_test_scene();
	if (!scene)
		return (1);

	init_player(scene);          /* set player.pos/dir/plane based on map.player_* */
	run_engine(scene);           /* your existing run_engine uses scene */

	free_test_scene(scene);
	return (0);
}
