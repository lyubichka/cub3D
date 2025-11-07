/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 19:30:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/06 18:46:47 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// void	render_scene(t_scene *scene, void *mlx, void *win)
// {
// 	// Here you would implement the raycasting and rendering logic.
// 	// For now, we will just fill the window with the ceiling and floor colors.

// 	int x, y;
// 	for (y = 0; y < scene->screen_height; y++)
// 	{
// 		for (x = 0; x < scene->screen_width; x++)
// 		{
// 			if (y < scene->screen_height / 2)
// 			{
// 				// Ceiling
// 				int color = scene->colors.ceiling_color;
// 				mlx_pixel_put(mlx, win, x, y, color);
// 			}
// 			else
// 			{
// 				// Floor
// 				int color = scene->colors.floor_color;
// 				mlx_pixel_put(mlx, win, x, y, color);
// 			}
// 		}
// 	}	
// }

void	render_scene(t_scene *scene, void *mlx, void *win)
{
	t_image	img;
	int		x;
	int		y;

	// 1️⃣ Create an empty image buffer to draw into
	init_image(mlx, &img, scene->screen_width, scene->screen_height);

	// 2️⃣ Loop through every pixel on screen
	y = 0;
	while (y < scene->screen_height)
	{
		x = 0;
		while (x < scene->screen_width)
		{
			if (y < scene->screen_height / 2)
				put_pixel(&img, x, y, scene->colors.ceiling_color);
			else
				put_pixel(&img, x, y, scene->colors.floor_color);
			x++;
		}
		y++;
	}

	// 4️⃣ Display the finished image in the window
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);

	// (Optional: free it after if you’ll re-render every frame)
	// mlx_destroy_image(mlx, img.img);
}

