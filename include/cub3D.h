/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:34:41 by veronikalub       #+#    #+#             */
/*   Updated: 2026/01/02 13:44:55 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// constants
# define MAX_MAP_HEIGHT 1000
# define MAX_MAP_WIDTH 1000

// key codes
// # define KEY_W      13    /* W */
// # define KEY_A      0     /* A */
// # define KEY_S      1     /* S */
// # define KEY_D      2     /* D */
// # define KEY_RIGHT	123   /* Left arrow */
// # define KEY_LEFT	124   /* Right arrow */
// # define KEY_ESC	53    /* Escape */

// key codes
# define KEY_W 119       /* W */
# define KEY_A 97        /* A */
# define KEY_S 115       /* S */
# define KEY_D 100       /* D */
# define KEY_LEFT 65363  /* Right arrow */
# define KEY_RIGHT 65361 /* Left arrow */
# define KEY_ESC 65307   /* Escape */

// texture identifiers
# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_EAST 2
# define TEX_WEST 3
# define TEX_COUNT 4

// minimap colors
# define MINIMAP_BG 0x202020
# define MINIMAP_WALL 0xFFFFFF
# define MINIMAP_PLAYER 0xFF0000
# define MINIMAP_DIR 0x00FF00

// structure for texture paths
typedef struct s_textures
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*sprite;
}					t_textures;

// structure for colors (0-255)
typedef struct s_colors
{
	int				floor[3];
	int				ceiling[3];
	int				floor_color;
	int				ceiling_color;
}					t_colors;

// structure for map and player position
typedef struct s_map
{
	char			**grid;
	int				width;
	int				height;
	int				player_x;
	int				player_y;
	char			player_dir;
}					t_map;

// structure for player (raycasting)
typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_player;

// main structure of the scene (what you give to your partner)
typedef struct s_scene
{
	int				screen_width;
	int				screen_height;
	t_textures		textures;
	t_colors		colors;
	t_map			map;
	int				save_bmp;
	t_player		player;
}					t_scene;

// structure for key states
typedef struct s_keys
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
	int				escape;
}					t_keys;

// parser contexts
typedef struct s_hdr_ctx
{
	char			**lines;
	t_scene			*scene;
	int				map_start;
	bool			seen_r;
	bool			seen_no;
	bool			seen_so;
	bool			seen_we;
	bool			seen_ea;
	bool			seen_s;
	bool			seen_f;
	bool			seen_c;
}					t_hdr_ctx;

typedef struct s_map_build_ctx
{
	char			**lines;
	int				start_line;
	int				map_lines;
	int				max_width;
	int				player_found;
	t_scene			*scene;
}					t_map_build_ctx;

// structure for image data
typedef struct s_image
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}					t_image;

// main structure for the cub3D program
typedef struct s_cub3d
{
	void			*mlx;
	void			*win;
	t_scene			scene;
	t_keys			keys;
	t_image			img;
	t_image			textures[TEX_COUNT];
}					t_cub3d;

// struct for ray
typedef struct s_ray
{
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

// minimap helper structures
typedef struct s_rect
{
	int				x;
	int				y;
	int				w;
	int				h;
}					t_rect;

typedef struct s_point
{
	int				x;
	int				y;
	int				radius;
}					t_point;

typedef struct s_line
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
}					t_line;

typedef struct s_line_state
{
	double			dx;
	double			dy;
	double			steps;
	double			sx;
	double			sy;
	double			cx;
	double			cy;
}					t_line_state;

typedef struct s_minimap_params
{
	int				tile_size;
	int				offset_x;
	int				offset_y;
	int				map_px_w;
	int				map_px_h;
}					t_minimap_params;

typedef struct s_minimap_draw
{
	t_image			*img;
	int				tile_size;
	int				offset_x;
	int				offset_y;
}					t_minimap_draw;

typedef struct s_minimap_max
{
	int				max_w;
	int				max_h;
}					t_minimap_max;

typedef struct s_tex_params
{
	t_image			*tex;
	int				tex_x;
	double			step;
	double			tex_pos;
}					t_tex_params;

typedef struct s_draw_stripe
{
	int				x;
	t_ray			*ray;
	t_tex_params	*params;
	int				screen_h;
}					t_draw_stripe;

typedef struct s_bmp_write
{
	unsigned char	*addr;
	int				line_len;
	int				bpp_bytes;
	int				width;
	int				pad_len;
}					t_bmp_write;

// functions for parser
t_scene				*parse_scene(const char *file_path, bool save_flag);
void				free_scene(t_scene *scene);
void				free_full_scene(t_scene *scene);
void				parse_resolution(char *line, t_scene *scene);
void				parse_texture(char *line, t_scene *scene);
void				parse_color(char *line, t_scene *scene);
void				parse_rgb(char **parts, int out[3]);
void				parse_map(char **lines, int map_start, t_scene *scene);
int					is_number_str(const char *s);

// helpers used by parser
t_scene				*init_scene(bool save_flag);
char				**read_lines_from_path(const char *path);
int					parse_header_until_map(char **lines, t_scene *scene);
int					is_map_line(const char *s);
void				handle_header_trim_ctx(t_hdr_ctx *ctx, char *trim);
void				print_error(const char *msg);
void				free_split(char **arr);
int					handle_kind_result(int kind, char *trim);
void				validate_after_header(t_hdr_ctx *ctx);
int					get_max_width(char **lines, int start, int end);
void				check_top_bottom_borders(t_scene *scene);
void				check_left_right_borders(t_scene *scene);
void				check_interior_cells(t_scene *scene);
int					is_player(char c);

/* cross-file header handling helpers */
void				dup_or_parse_texture(t_hdr_ctx *ctx, char *trim, bool *seen,
						const char *dup_msg);
void				dup_or_parse_resolution(t_hdr_ctx *ctx, char *trim,
						bool *seen);
void				dup_or_parse_color(t_hdr_ctx *ctx, char *trim, bool *seen,
						const char *dup_msg);
int					handle_no(t_hdr_ctx *ctx, char *trim);
int					handle_so(t_hdr_ctx *ctx, char *trim);
int					handle_we(t_hdr_ctx *ctx, char *trim);
int					handle_ea(t_hdr_ctx *ctx, char *trim);
int					handle_s(t_hdr_ctx *ctx, char *trim);

// execution
void				run_engine(t_scene *scene);
int					frame_loop(void *param);

// functions for rendering
void				render_scene(t_cub3d *cub);
void				init_image(void *mlx, t_image *img, int width, int height);
void				put_pixel(t_image *img, int x, int y, int color);
void				compute_ray(t_cub3d *cub, int x, t_ray *ray);
void				perform_dda(t_cub3d *cub, t_ray *ray);
void				compute_wall_height(t_cub3d *cub, t_ray *ray);
void				draw_vertical_stripe_textured(t_image *img, t_cub3d *cub,
						int x, t_ray *ray);
int					save_bmp_file(t_image *img, int width, int height,
						const char *filename);
int					save_mode_render_and_write(t_scene *scene,
						const char *out_filename);

// save helper functions
int					write_file_header(FILE *f, uint32_t file_size,
						uint32_t pixel_offset);
int					write_dib_header(FILE *f, int width, int height);
int					write_pixel_data(FILE *f, t_image *img, int width,
						int height);
uint32_t			build_pixel(unsigned char *p, int bpp_bytes);
void				extract_rgb(uint32_t pixel, unsigned char *buf);
int					write_row_padding(FILE *f, int pad_len);
int					prepare_offscreen_cub(t_cub3d *cub, t_scene *scene);
int					create_offscreen_image(t_cub3d *cub);
void				cleanup_offscreen(t_cub3d *cub);

// rendering helper functions
int					get_texture_index(t_ray *ray);
double				calc_wall_x(t_cub3d *cub, t_ray *ray);
int					calc_tex_x(double wall_x, t_image *tex, t_ray *ray);
void				init_texture_params(t_cub3d *cub, t_ray *ray,
						t_tex_params *params);

// key handling functions
int					key_press(int keycode, void *param);
int					key_release(int keycode, void *param);
void				handle_keys(t_cub3d *cub);

// movement and rotation functions
void				move_forward(t_cub3d *cub, double speed);
void				move_backward(t_cub3d *cub, double speed);
void				strafe_left(t_cub3d *cub, double speed);
void				strafe_right(t_cub3d *cub, double speed);
void				rotate_left(t_cub3d *cub, double speed);
void				rotate_right(t_cub3d *cub, double speed);

// functions for player
void				init_player(t_scene *scene);

// utility functions
void				print_error(const char *msg);
int					handle_close(void *param);

// graphics functions
void				init_graphics(t_cub3d *cub);
void				load_textures(t_cub3d *cub);
void				free_textures(t_cub3d *cub);
int					get_tex_color(t_image *tex, int tx, int ty);
void				draw_minimap(t_cub3d *cub, t_image *img);

// minimap helper functions
void				compute_minimap_params(t_cub3d *cub,
						t_minimap_params *params);
void				draw_map_cells(t_cub3d *cub, t_minimap_draw *draw);
void				draw_player_on_minimap(t_cub3d *cub, t_minimap_draw *draw);
void				draw_filled_rect(t_image *img, t_rect rect, int color);
void				draw_line(t_image *img, t_line line, int color);
void				draw_filled_square_centered(t_image *img, t_point center,
						int color);

#endif
