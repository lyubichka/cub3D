/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:34:41 by veronikalub       #+#    #+#             */
/*   Updated: 2025/10/15 17:21:06 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// constants 
# define MAX_MAP_HEIGHT 100
# define MAX_MAP_WIDTH  100

// structure for texture paths
typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
}	t_textures;

// structure for colors (0-255)
typedef struct s_colors
{
	int	floor[3];
	int	ceiling[3];
	int	floor_color;   // объединённый int 0xRRGGBB 
	int	ceiling_color; // объединённый int 0xRRGGBB
}	t_colors;

// structure for map and player position
typedef struct s_map
{
	char	**grid;       // massiv[height][width]
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;   // 'N', 'S', 'E', 'W'
}	t_map;

// main structure of the scene (what you give to your partner)
typedef struct s_scene
{
	int			screen_width;
	int			screen_height;
	t_textures	textures;
	t_colors	colors;
	t_map		map;
	int			save_bmp; // 1 if "--save", else 0
}	t_scene;

// structure for key states
typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	escape;
}	t_keys;


// functions for parser
t_scene	*parse_scene(const char *file_path, bool save_flag);
void	free_scene(t_scene *scene);
void	parse_resolution(char *line, t_scene *scene);
void	parse_texture(char *line, t_scene *scene);
void	parse_color(char *line, t_scene *scene);
void	parse_map(int fd, t_scene *scene, char *first_line);
void	validate_map(t_map *map);
int		create_rgb_int(int r, int g, int b);

#endif


// for you now
// creates a window using MiniLibX:

// mlx_new_window(scene->screen_width, scene->screen_height, "cub3D");

// Loads textures using the paths:
// scene->textures.north, south, etc.

// Initializes the player's position:
// scene->map.player_x, player_y, player_dir.

// Implements movement (WASD, arrows).

// Does raycasting and rendering (one frame).

// Adds the --save flag (if scene->save_bmp == 1).


// my main my function will be t_scene *parse_scene(const char *path, bool save_flag);