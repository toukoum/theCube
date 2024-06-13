/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:11:26 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/28 15:21:04 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	init_args(t_args *args)
{
	char	*line;

	line = get_next_line(args->fd);
	while (line)
	{
		args->start_map++;
		if (parse_line(line, args))
			return ;
		free(line);
		line = get_next_line(args->fd);
	}
	free(line);
	return (close(args->fd), quit(MISSING_MAP));
}

/**
 * @brief check the path of the .cub file
 */
void	check_path(int *fd, char *path)
{
	if (is_dir(path))
		return (quit(FILE_DIR));
	if (!check_extension(path, ".cub"))
		return (quit(EXTENSION_NAME));
	(*fd) = open(path, O_RDONLY);
	if ((*fd) == -1)
		return (quit(WRONG_FILE));
}

/**
 * @brief
 * 1- check if file name is correct (not folder, .cub extension, ...)
 * 2- initialise and check args value with gnl
 * 3- initialise and check the map
 *
* @param args struct for all the arguments of the parse file
* @param path path of the map
*/
void	parse(t_args *args, char *path)
{
	ft_bzero(args, sizeof(t_args));
	args->path_file = path;
	init_all_value(args);
	check_path(&args->fd, path);
	init_args(args);
	close(args->fd);
}
