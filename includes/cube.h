/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:22:07 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/19 20:20:20 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CUBE_H__
# define __CUBE_H__


# ifdef __APPLE__
  #define LINUX 0
  #define MY_DIR O_DIRECTORY
# elif __linux__
  #define LINUX 1
  #define MY_DIR __O_DIRECTORY
# endif


# include "../libft-boost/ft_printf/includes/ft_printf.h"
# include "../libft-boost/gnl/includes/get_next_line_bonus.h"
# include "../libft-boost/libft_mandatory/includes/libft.h"
# include <fcntl.h> // open
# include <mlx.h>
#  include <X11/X.h>
#  include <X11/keysym.h>
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
}					t_args;

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
# define MISSING_ARG 6
# define WRONG_ARG 7

// =========================== FUNCTION ===========================

// -> parsing
void				parse(t_args *args, char *path);
void				init_color(t_color *color_struct);
bool				is_space(char c);
bool				is_args_full(t_args *args);
bool				check_extension(char *path, char *extension);
bool				is_dir(char *path);
void				goto_next_char(int *i, char *line);
int					min_atoi_boost(char *line, int *i, int *err);
bool				is_texture_id(char *line, int i);
void				parse_color_line(t_args *args, char *line, int i);
void				parse_line(char *line, t_args *args);
bool				good_number(int i, char *line);

// -> quit
void				quit(int exit_code);

#endif