/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:31:29 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/18 11:54:58 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <X11/keysym.h>
# define LINUX 1
# define MY_DIR __O_DIRECTORY

# include "../libft-boost/ft_printf/includes/ft_printf.h"
# include "../libft-boost/gnl/includes/get_next_line_bonus.h"
# include "../libft-boost/libft_mandatory/includes/libft.h"
# include <X11/X.h>
# include <fcntl.h> // open
# include <math.h>
# include <mlx.h>
# include <stdbool.h> // boolean
# include <unistd.h>  // open, write

// =========================== EXIT CODE ===========================
// error code
# define ALL_PAS_GOOD 0
# define NUMBERS_ARGC 1
# define WRONG_FILE 2
# define EXTENSION_NAME 3
# define FILE_DIR 4
# define CLONE_ARGS 5
# define MISSING_MAP 6
# define WRONG_ARG 7
# define MPTY_LINE_MAP 8
# define INVALID_CHARACTER 9
# define MAP_NOT_LAST 10
# define MISSING_ARG 11
# define MALLOC_ERROR 71
# define WALL_SURR 12
# define ALL_GOOD 13
# define NO_PLAYER 14
# define DUP_PLAYER 15
# define SUCESS 16

// shell color
# define RED "\e[1;31m"
# define REDL "\e[0;31m"
# define YELLOWB "\e[1;93m"
# define GREENB "\e[1;92m"
# define RESET "\e[0m"

# ifndef DEBUG
#  define DEBUG 0
# endif

# define WWIN 1280
# define HWIN 720
# define WMAP 256
# define HMAP 144

# define TSIZE 15

// color for mlx
# define CBLUE 0x000000FF
# define CWHITE 0x00FFFFFF
# define CGREEN 0xB5E550
# define CRED 0x00FF0000
# define CBLACK 0x00000000
# define CCYAN 0x0000FFFF
# define CMAGENTA 0x00FF00FF
# define CYELLOW 0x00E8E337
# define CORANGE 0x00FA991C
# define CPINK 0x00FFC0CB
# define CLIME 0x0000FF80

# define CWALL 0x222831
# define CGROUND 0xEEEEEE
# define CUNDEFINED 0xAA96DA
# define CDOOR 0x00ADB5
# define CPLAYER 0xf96160

# define CRAY 0xCAE9EA

# define MOVESPEED 0.03
# define ROTSPEED 0.03
# define CHANGEFOV 2
# define SENSITIVITY 0.0000001

# define HITBOX_RADIUS 0.6

# define NSPRITE 14

// =========================== STRUCT ===========================
typedef struct s_color
{
	bool			is_correct;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	int				color;

}					t_color;

typedef struct s_coord
{
	double			x;
	double			y;
}					t_coord;

typedef struct s_int_coord
{
	int				x;
	int				y;
}					t_int_coord;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct s_door
{
	t_int_coord		pos;
	bool			is_open;
}					t_door;

typedef struct s_args
{
	int				fd;
	char			*pathn;
	char			*paths;
	char			*pathw;
	char			*pathe;
	char			*ground;
	char			*sky;
	t_color			floor_col;
	t_color			ceil_col;
	char			**map;
	double			pos_x;
	double			pos_y;
	int				width;
	int				height;
	bool			is_correct_pos;
	bool			is_floor_texture;
	char			start_angle;
	char			*path_file;
	int				start_map;
	int				ndoor;
	t_door			**doors;

}					t_args;

typedef struct s_player
{
	double			x;
	double			y;
	char			start_angle;
}					t_player;

typedef struct s_ray
{
	int				line_height;
	t_coord			raydir;
	t_coord			d;
	t_int_coord		map;
	t_coord			sidist;
	double			perpdist;
	t_int_coord		step;
	int				side_hit;
	t_int_coord		start_point;
	t_int_coord		end_point;
	int				draw_start;
	int				draw_end;
	int				tex_x;
	bool			is_ray_door;
	double			offset;
	t_img			*texture;

}					t_ray;

typedef struct s_rayfloor
{
	t_coord			raydir0;
	t_coord			raydir1;
	t_coord			d;
	t_coord			floor;
	t_coord			cell;
	t_int_coord		idx;
	double			posz;
	double			p;
	double			rowdist;
}					t_rayfloor;
typedef struct s_map
{
	char			*pathn;
	char			*paths;
	char			*pathw;
	char			*pathe;
	t_color			floor_col;
	t_color			ceil_col;
	char			**map;
	int				width;
	int				height;
}					t_map;

typedef struct s_sprite
{
	int				spritheight;
	int				spritwidth;
	int				spritescrinx;
	t_int_coord		drawstart;
	t_int_coord		drawend;
	int				texx;
	t_img			texture;
	t_coord			pos;
	int				idx_textures;
	bool			play;
	int				nframe;
}					t_sprite;

typedef struct s_cub
{
	t_args			*map;
	t_player		player;
	t_img			img;
	t_img			mmap;
	void			*mlx;
	void			*win;
	t_coord			dir;
	t_coord			plane;
	t_img			texn;
	t_img			texs;
	t_img			texe;
	t_img			texw;
	t_img			sky;
	t_img			ground;

	t_sprite		sprites[NSPRITE];

	t_img			sprites_textures[NSPRITE][100];
	double			walldist[WWIN];
	double			dist_ps[NSPRITE][2];
	t_coord			transform;
	double			inv_matrice;

	int				frame_counter;
	int				frame_sprite;
	bool			can_move;
	bool			display_help;

	t_img			door;
	t_door			**doors;
	int				keybuffer[100000];
	double			rot_speed;
}					t_cub;

// =========================== EVENT MLX ===========================
enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

// =========================== FUNCTION ===========================

// -> parsing
void				parse(t_args *args, char *path);
void				init_all_value(t_args *args);
bool				is_space(char c);
bool				is_args_full(t_args *args);
bool				check_extension(char *path, char *extension);
bool				is_dir(char *path);
void				goto_next_char(int *i, char *line);
int					min_atoi_boost(char *line, int *i, int *err);
bool				is_texture_id(char *line, int i);
void				parse_color_line(t_args *args, char *line, int i);
int					parse_line(char *line, t_args *args);
bool				good_number(int i, char *line);
void				parse_map(t_args *args, char *line);
void				exit_parse_map(t_args *args, int exit_code, bool close_fd);
bool				is_empty_line(char *line);
void				get_line_width(t_args *args, char *line);
void				str_copy_cube(char *dst, char *src);
void				check_map(t_args *args, int i, int j, char c);
void				store_map(t_args *args);
void				init_all_textures(t_cub *cub);
bool				is_player_door_char(char c);

// -> quit
void				quit(int exit_code);
void				free_all_map(t_args *args, int exit_code);
void				free_malloced_line_map(t_args *args, int i);
void				quit_cub(int exit_code);
void				free_cub(t_cub *cub);
void				free_arg(t_args *args);

// mlx
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);
int					render(t_cub *cub);
void				draw_rect(t_img *img, t_int_coord point,
						t_int_coord dimension, int color);
void				change_fov(t_cub *cub, int keycode);
void				draw_line(t_img *img, t_coord x1, t_coord x2, int color);

// init
void				init_mlx(t_cub *cub);
void				init_cub(t_cub *cub, t_args *args);
void				init_handle(t_cub *cub);

// minimap
void				draw_all(t_cub *cub);
int					get_pixel_color(char **map, t_int_coord *mapIndex);
void				draw_border_minimap(t_cub *cub);
void				draw_line_minimap(t_img *img, t_coord x1, t_coord x2,
						int color);

// raycasting
void				raycasting(t_cub *cub);
void				init_ray(t_cub *cub, t_ray *ray, double camX);
int					get_wall_color(t_int_coord *mapIndex, char **map,
						int side_hit);
void				assign_ray_dist(int x, double dist, t_cub *cub);
void				draw_column(int x, t_ray *ray, t_cub *cub);

// event mlx
int					handle_close_win(t_cub *cub);
int					handle_key(int keycode, t_cub *cub);
int					handle_key_release(int keycode, t_cub *cub);
void				process_key_input(t_cub *cub);
int					handle_mouse(int x, int y, t_cub *cub);

// move player
void				move_player(int keycode, t_cub *cub);
void				rotate_player(int keycode, t_cub *cub);
int					handle_mouse_click(int keycode, int x, int y, t_cub *cub);

// divers
void				draw_log_player(t_cub *cub);
void				draw_fov(t_cub *cub);
char				*get_value_float(double value);
void				open_door(t_cub *cub);

// floor and ceiling
void				draw_floor_ceil(t_cub *cub);
bool				is_door_close(char **map, int x, int y, t_door **doors);

// sprites
void				sprites(t_cub *cub);
void				init_pos_sprite(t_cub *cub);
bool				is_sprite_viewable(t_cub *cub, int x);
void				sort_dist_player_sprites(double dist_ps[NSPRITE][2]);
void				draw_sprites(t_cub *cub);
void				calculate_pos_relative_sprite(int i, t_cub *cub);
void				play_animation(t_cub *cub);
void				calculate_pos_relative_sprite(int i, t_cub *cub);
bool				is_door_close(char **map, int x, int y, t_door **doors);

#endif