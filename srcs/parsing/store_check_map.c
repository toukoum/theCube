/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_check_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:07:29 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/22 20:09:59 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

/**
 * @brief check if all the wall is correctly surrounded by 1,
 * including diagonal wall
 *  1
 * 101 ==> not valid map
 *  1
 */
static bool	check_wall(t_args *args, int i, int j, int width)
{
	char	**map;

	map = args->map;
	if (i > 0 && (map[i - 1][j] == '\0' || map[i - 1][j] == ' '))
		return (false);
	if (i < args->height - 1 && (map[i + 1][j] == '\0' || map[i + 1][j] == ' '))
		return (false);
	if (j > 0 && (map[i][j - 1] == '\0' || map[i - 1][j - 1] == ' '))
		return (false);
	if (j < width - 1 && map[i][j + 1] == '\0')
		return (false);
	if (i > 0 && j > 0 && (map[i - 1][j - 1] == '\0' || map[i - 1][j
			- 1] == ' '))
		return (false);
	if (i > 0 && j < width - 1 && map[i - 1][j + 1] == '\0')
		return (false);
	if (i < args->height - 1 && j > 0 && (map[i + 1][j - 1] == '\0' || map[i
			- 1][j - 1] == ' '))
		return (false);
	if (i < args->height - 1 && j < width - 1 && map[i + 1][j + 1] == '\0')
		return (false);
	return (true);
}

static void	set_pos_door_player(t_args *args, int i, int j)
{
	if (args->map[i][j] == 'D')
	{
		args->doors[args->ndoor] = malloc(sizeof(t_door));
		if (!args->doors[args->ndoor])
			return (free_all_map(args, MALLOC_ERROR));
		args->doors[args->ndoor]->pos = (t_int_coord){j, i};
		args->doors[args->ndoor]->is_open = false;
		args->ndoor++;
		return ;
	}
	if (args->is_correct_pos)
		return (free_all_map(args, DUP_PLAYER));
	else
	{
		args->is_correct_pos = true;
		args->pos_x = j + 0.5;
		args->pos_y = i + 0.5;
		args->start_angle = args->map[i][j];
	}
}

/**
 * @brief function moche sa mere mais flemme de
 * la refacto (meme si je devrais...)
 * en gros elle verifie que ya bien des murs de partout
 * et que ya pas de joueur en double
 */
void	check_map(t_args *args, int i, int j, char c)
{
	int	width_line;
	int	first_j;

	while (args->map[i])
	{
		j = 0;
		goto_next_char(&j, args->map[i]);
		first_j = j;
		width_line = ft_strlen(args->map[i] + j);
		while (args->map[i][j])
		{
			c = args->map[i][j];
			if (is_player_door_char(c))
				set_pos_door_player(args, i, j);
			if ((i == 0 || i == args->height - 1 || j == first_j
					|| j == ft_strlen(args->map[i]) - 1) && c != '1')
				return (free_all_map(args, WALL_SURR));
			else if (c != '1' && !check_wall(args, i, j, width_line))
				return (free_all_map(args, WALL_SURR));
			j++;
		}
		i++;
	}
}

static void	store_map_lines(t_args *args, char *line)
{
	int	i;

	i = 0;
	while (line && !is_empty_line(line))
	{
		args->map[i] = ft_calloc(args->width + 1, sizeof(char));
		if (!args->map[i])
			return (free(line), free_malloced_line_map(args, i - 1));
		str_copy_cube(args->map[i], line);
		free(line);
		line = get_next_line(args->fd);
		i++;
	}
	free(line);
}

void	store_map(t_args *args)
{
	char	*line;
	int		i;

	i = 0;
	args->map = malloc((args->height + 1) * sizeof(char *));
	if (!args->map)
		return (exit_parse_map(args, MALLOC_ERROR, false));
	args->map[args->height] = NULL;
	close(args->fd);
	args->fd = open(args->path_file, O_RDONLY);
	if (args->fd == -1)
		return (exit_parse_map(args, WRONG_FILE, false));
	line = get_next_line(args->fd);
	while (line && i < (args->start_map - 1))
	{
		free(line);
		line = get_next_line(args->fd);
		i++;
	}
	store_map_lines(args, line);
}
