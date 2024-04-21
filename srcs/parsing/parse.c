/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:11:26 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/21 11:02:54 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	init_args(t_args *args)
{
	char	*result;

	ft_printf("fd: %d\n", (args->fd));
	result = get_next_line(args->fd);
	while (result)
	{
		args->start_map++;
		if (parse_line(result, args))
			return ;
		free(result);
		result = get_next_line(args->fd);
	}
	free(result);
	return (close(args->fd), quit(MISSING_MAP));
}

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
	init_color(args);
	check_path(&args->fd, path);
	init_args(args);
	close(args->fd);
}
