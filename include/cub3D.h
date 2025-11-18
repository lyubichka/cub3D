/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:34:41 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/18 17:20:03 by haiqbal          ###   ########.fr       */
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

// structure for player (raycasting)
typedef struct s_player
{
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
}   t_player;

// main structure of the scene (what you give to your partner)
typedef struct s_scene
{
	int			screen_width;
	int			screen_height;
	t_textures	textures;
	t_colors	colors;
	t_map		map;
	int			save_bmp; // 1 if "--save", else 0
	t_player	player;
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

// parser contexts
typedef struct s_hdr_ctx
{
    char    **lines;
    t_scene *scene;
    int     map_start;
    bool    seen_r;
    bool    seen_no;
    bool    seen_so;
    bool    seen_we;
    bool    seen_ea;
    bool    seen_s;
    bool    seen_f;
    bool    seen_c;
}   t_hdr_ctx;

typedef struct s_map_build_ctx
{
    char **lines;
    int   start_line;
    int   map_lines;
    int   max_width;
    int   player_found;
    t_scene *scene;
}   t_map_build_ctx;

// main structure for the cub3D program
typedef struct s_cub3d
{
	void	*mlx;
	void	*win;
	t_scene	scene;
	t_keys	keys;
}	t_cub3d;

// structure for image data
typedef struct s_image {
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
} t_image;

// struct for ray
typedef struct s_ray
{
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	int stepX;
	int stepY;
	int hit;
	int side;
	double perpWallDist;
	int lineHeight;
	int drawStart;
	int drawEnd;
}	t_ray;


// functions for parser
t_scene	*parse_scene(const char *file_path, bool save_flag);
void	free_scene(t_scene *scene);
void	parse_resolution(char *line, t_scene *scene);
void	parse_texture(char *line, t_scene *scene);
void	parse_color(char *line, t_scene *scene);
void    parse_rgb(char **parts, int out[3]);
void	parse_map(char **lines, int map_start, t_scene *scene);
void	validate_map(t_map *map);
int		is_number_str(const char *s);

// helpers used by parser
t_scene *init_scene(bool save_flag);
char   **read_lines_from_path(const char *path);
int      parse_header_until_map(char **lines, t_scene *scene);
int      is_map_line(const char *s);
void     handle_header_trim_ctx(t_hdr_ctx *ctx, char *trim);
void     print_error(const char *msg);
void     run_engine(t_scene *scene);
void     free_split(char **arr);
int      handle_kind_result(int kind, char *trim);
void     validate_after_header(t_hdr_ctx *ctx);

/* cross-file header handling helpers */
void     dup_or_parse_texture(t_hdr_ctx *ctx, char *trim, bool *seen,
                              const char *dup_msg);
void     dup_or_parse_resolution(t_hdr_ctx *ctx, char *trim, bool *seen);
void     dup_or_parse_color(t_hdr_ctx *ctx, char *trim, bool *seen,
                            const char *dup_msg);
int      handle_no(t_hdr_ctx *ctx, char *trim);
int      handle_so(t_hdr_ctx *ctx, char *trim);
int      handle_we(t_hdr_ctx *ctx, char *trim);
int      handle_ea(t_hdr_ctx *ctx, char *trim);
int      handle_s(t_hdr_ctx *ctx, char *trim);

// execution

// functions for rendering
void	run_engine(t_scene *scene);
void	render_scene(t_cub3d *cub);
void	init_image(void *mlx, t_image *img, int width, int height);
void	put_pixel(t_image *img, int x, int y, int color);

// functions for player
void	init_player(t_scene *scene);

// utility functions
void	print_error(const char *msg);

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
