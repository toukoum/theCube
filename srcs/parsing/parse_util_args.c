/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:12:12 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/19 20:20:10 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	init_color(t_color *color_struct)
{
	color_struct->is_correct = false;
	color_struct->b = 0;
	color_struct->g = 0;
	color_struct->r = 0;
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
	return (args->pathE && args->pathN && args->pathS && args->pathO
		&& args->ceilColor.is_correct && args->floorColor.is_correct);
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}
