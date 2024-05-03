/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:22:07 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/03 17:19:34 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CUBE_H__
# define __CUBE_H__

# ifdef __APPLE__
#  define LINUX 0
#  define MY_DIR O_DIRECTORY
# elif __linux__
#  include <X11/keysym.h>
#  define LINUX 1
#  define MY_DIR __O_DIRECTORY
# endif

# include "../libft-boost/ft_printf/includes/ft_printf.h"
# include "../libft-boost/gnl/includes/get_next_line_bonus.h"
# include "../libft-boost/libft_mandatory/includes/libft.h"
# include <X11/X.h>
# include <fcntl.h> // open
# include <math.h>
# include <mlx.h>
# include <stdbool.h> // boolean
# include <unistd.h>  // open, write

// =========================== STRUCT ===========================
typedef struct s_color
{
	bool			is_correct;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	int				color;

}					t_color;

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

typedef struct s_args
{
	int				fd;
	char			*pathN;
	char			*pathS;
	char			*pathW;
	char			*pathE;
	char			*ground;
	char			*sky;
	t_color			floorColor;
	t_color			ceilColor;
	char			**map;
	double			pos_x;
	double			pos_y;
	int				width;
	int				height;
	bool			is_correct_pos;
	char start_angle; // 'N', 'S', 'E', 'W'
	char			*path_file;
	int				start_map;
}					t_args;

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

typedef struct s_player
{
	double			x;
	double			y;
	char			start_angle;
}					t_player;

typedef struct s_ray
{
	int				line_height;
	t_coord			rayDir;
	t_coord			d;
	t_int_coord		map;
	t_coord			sideDist;
	double			perpWallDist;
	t_int_coord		step;
	int				side_hit;
	t_int_coord		start_point;
	t_int_coord		end_point;
}					t_ray;

typedef struct s_rayfloor
{
	t_coord			rayDir0;
	t_coord			rayDir1;
	t_coord			d;
	t_coord			floor;
	t_coord			cell;
	t_int_coord		idx;
	double			posZ;
	double			p;
	double			rowDist;
}					t_rayfloor;
typedef struct s_map
{
	char			*pathN;
	char			*pathS;
	char			*pathW;
	char			*pathE;
	t_color			floorColor;
	t_color			ceilColor;
	char			**map;
	int				width;
	int				height;
}					t_map;

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
	t_img			texN;
	t_img			texS;
	t_img			texE;
	t_img			texW;
	t_img			sky;
	t_img			ground;

	double			distRayL;
	double			distRayC;
	double			distRayR;

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

// =========================== EXIT CODE ===========================
// error code
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
# define MALLOC_ERROR 11
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

# define WWIN 1280 // width of window
# define HWIN 720 // height of window
# define WMAP 20 * WWIN / 100 // width of minimap
# define HMAP 20 * HWIN / 100 // height of minimap

# define TSIZE 15 // taille d'un carreau de la minimap

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

# define CWALL 0x032539
# define CGROUND 0xF5F7F8
# define CUNDEFINED 0x1E1E1E
# define CPLAYER 0xf96160

# define CRAY 0xCAE9EA

# define MOVESPEED 0.1
# define ROTSPEED 0.1
# define CHANGEFOV 0.1
// =========================== FUNCTION ===========================

// -> parsing
void				parse(t_args *args, char *path);
void				init_color(t_args *args);
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
void				check_map(t_args *args, int i, int j);
void				store_map(t_args *args);
void				init_all_textures(t_cub *cub);

// -> quit
void				quit(int exit_code);
void				free_all_map(t_args *args, int exit_code);
void				exit_free_map(t_args *args, int i);
void				quit_cub(int exit_code);
void				free_cub(t_cub *cub);
void				free_arg(t_args *args);

// mlx
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);
void				render(t_cub *cub);
void				draw_rect(t_img *img, t_int_coord point,
						t_int_coord dimension, int color);
void				change_fov(t_cub *cub, int keycode);
void				draw_line(t_img *img, t_coord x1, t_coord x2, int color);

// init
void				init_mlx(t_cub *cub);
void				init_cub(t_cub *cub, t_args *args);

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

// event mlx
int					handle_close_win(t_cub *cub);
int					handle_key(int keycode, t_cub *cub);

// move player
void				move_player(int keycode, t_cub *cub, t_int_coord map_index);
void				rotate_player(int keycode, t_cub *cub);

// divers
void				draw_log_player(t_cub *cub);
void				draw_fov(t_cub *cub);
char				*get_value_float(double value);

// floor and ceiling
void				draw_floor_ceil(t_cub *cub);

# ifdef __APPLE__
#  define XK_Escape 53
#  define XK_q 12
#  define XK_w 13
#  define XK_e 14
#  define XK_a 0
#  define XK_s 1
#  define XK_d 2
#  define XK_Up 126
#  define XK_Down 125
#  define XK_Left 123
#  define XK_Right 124
#  define XK_plus 24
#  define XK_minus 27
# endif

#endif