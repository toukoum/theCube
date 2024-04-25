/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:22:07 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/25 12:12:07 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CUBE_H__
# define __CUBE_H__

# ifdef __APPLE__
#  define LINUX 0
#  define MY_DIR O_DIRECTORY
# elif __linux__
#  define LINUX 1
#  include <X11/X.h>
#  include <X11/keysym.h>
#  define MY_DIR __O_DIRECTORY
# endif

# include "../libft-boost/ft_printf/includes/ft_printf.h"
# include "../libft-boost/gnl/includes/get_next_line_bonus.h"
# include "../libft-boost/libft_mandatory/includes/libft.h"
# include <fcntl.h> // open
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

}					t_color;

typedef struct s_args
{
	int				fd;
	char			*pathN;
	char			*pathS;
	char			*pathO;
	char			*pathE;
	t_color			floorColor;
	t_color			ceilColor;
	char			**map;
	size_t			pos_x;
	size_t			pos_y;
	size_t			width;
	size_t			height;
	bool			is_correct_pos;
	char start_angle; // 'N', 'S', 'E', 'W'
	char			*path_file;
	int				start_map;
}					t_args;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_cub
{
	t_args			*arg;
	t_img			img;
	t_img			mmap;
	void			*mlx;
	void			*win;
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
# define WMAP 15 * WWIN / 100 // width of minimap
# define HMAP 15 * HWIN / 100 // height of minimap
# define TSIZE 15 // taille d'un carreau de la minimap

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
void				check_map(t_args *args, size_t i, size_t j);
void				store_map(t_args *args);
void				goto_next_char_sizet(size_t *i, char *line);

// -> quit
void				quit(int exit_code);
void				free_all_map(t_args *args, int exit_code);
void				exit_free_map(t_args *args, int i);
void				quit_cub(int exit_code);
void				free_cub(t_cub *cub);

// mlx
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);

// init
void				init_mlx(t_cub *cub);

# ifdef __APPLE__
#  define XK_Escape 53
#  define XK_Q 12
#  define XK_W 13
#  define XK_E 14
#  define XK_A 0
#  define XK_S 1
#  define XK_D 2
#  define XK_Up 126
#  define XK_Down 125
#  define XK_Left 123
#  define XK_Right 124
# endif

#endif