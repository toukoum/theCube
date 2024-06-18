/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:12:12 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/18 11:46:31 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	init_all_value(t_args *args)
{
	args->ndoor = 0;
	args->ceil_col.is_correct = false;
	args->ceil_col.b = 0;
	args->ceil_col.g = 0;
	args->ceil_col.r = 0;
	args->floor_col.is_correct = false;
	args->floor_col.b = 0;
	args->floor_col.g = 0;
	args->floor_col.r = 0;
	args->pos_x = 0;
	args->pos_y = 0;
	args->is_correct_pos = false;
	args->width = 0;
	args->height = 0;
	args->start_angle = 'Z';
	args->pathe = NULL;
	args->pathn = NULL;
	args->paths = NULL;
	args->pathw = NULL;
	args->ground = NULL;
	args->sky = NULL;
	args->start_map = 0;
	args->is_correct_pos = false;
}

bool	is_dir(char *path)
{
	int		fd;
	bool	result;

	result = false;
	fd = open(path, MY_DIR);
	if (fd >= 0)
	{
		result = true;
		close(fd);
	}
	return (result);
}

/**
 * @brief
 *
 * @param path
 * @return true => 1 if the path is ok
 * @return false  => 0 otherwise
 */
bool	check_extension(char *path, char *extension)
{
	return (!(ft_strncmp(extension, path + (ft_strlen(path) - 4), 4)));
}

/**
 * @brief
 *
 * @param args
 * @return true if all args is correctly fullfield
 * @return false otherwise
 */
bool	is_args_full(t_args *args)
{
	return (args->pathe && args->pathn && args->paths && args->pathw
		&& ((args->ceil_col.is_correct && args->floor_col.is_correct)
			|| (args->sky && args->ground)));
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}
