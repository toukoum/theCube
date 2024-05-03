/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:12:12 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/03 16:31:37 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	init_color(t_args *args)
{
	args->ceilColor.is_correct = false;
	args->ceilColor.b = 0;
	args->ceilColor.g = 0;
	args->ceilColor.r = 0;
	args->floorColor.is_correct = false;
	args->floorColor.b = 0;
	args->floorColor.g = 0;
	args->floorColor.r = 0;
	args->pos_x = 0;
	args->pos_y = 0;
	args->is_correct_pos = false;
	args->width = 0;
	args->height = 0;
	args->start_angle = 'Z';
	args->pathE = NULL;
	args->pathN = NULL;
	args->pathS = NULL;
	args->pathW = NULL;
	args->ground = NULL;
	args->sky = NULL;
	args->start_map = 0;
}

bool	is_dir(char *path)
{
	int		fd;
	bool	result;

	result = false;
	if (LINUX)
		fd = open(path, MY_DIR);
	else
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
	return (args->pathE && args->pathN && args->pathS && args->pathW
		&& args->ceilColor.is_correct && args->floorColor.is_correct && args->sky && args->ground);
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}
