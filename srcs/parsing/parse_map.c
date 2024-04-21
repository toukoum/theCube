/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:23:01 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/21 11:37:00 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	get_dimensions(t_args *args, char *line)
{
	while (line && !is_empty_line(line))
	{
		get_line_width(args, line);
		args->height++;
		free(line);
		line = get_next_line(args->fd);
	}
	free(line);
	line = get_next_line(args->fd);
	while (line)
	{
		if (!is_empty_line(line))
			return (free(line), exit_parse_map(args, MAP_NOT_LAST, true));
		free(line);
		line = get_next_line(args->fd);
	}
	if (line)
		free(line);
}

void store_map_line(t_args *args, char *line)
{
	int i;

	i = 0;
	while (line && !is_empty_line(line))
	{
		args->map[i] = ft_calloc(args->width, sizeof(char));
		if (!args->map[i])
			exit_free_map(args, i - 1);
		str_copy_cube(args->map[i], line);
		free(line);
		line = get_next_line(args->fd);
		i++;
	}
}


void store_map(t_args *args)
{
	char *line;
	int i;

	i = 0;
	args->map = malloc((args->height + 1) * sizeof(char *));
	if (!args->map)
		return (exit_parse_map(args, MALLOC_ERROR, false));
	args->map[args->height] = NULL;
	args->fd = open(args->path_file, O_RDONLY);
	if (args->fd == -1)
		return (exit_parse_map(args, WRONG_FILE, false));
	line = get_next_line(args->fd);
	while (line && i < args->start_map - 1)
	{
		free(line);
		line = get_next_line(args->fd);
		i++;
	}
	store_map_line(args, line);
	close(args->fd);
}

//void check_map(t_args *args, int i, int j)
//{
	
//	while (args->map[i])
//	{
//		j = 0;
//		while (args->map[j])
//		{
//			if ((i == 0 || i == args->height - 1 && (args->map[i][j] != '1')) || (j = 0 || j = args.wi))
//				return (free_all_map())
//		}
		
//	}
//}

/**
 * @brief args are correct
 * need to check and store map
 * if any pb
 * 	-> close(fd)
 *  -> free(args.path) * 4
 *
 *  need to free line
 */
void	parse_map(t_args *args, char *line)
{
	get_dimensions(args, line);
	store_map(args);
	for (size_t i = 0; i < args->height; i++)
	{
		for (size_t j = 0; j < args->width; j++)
		{
			ft_printf("%c ", args->map[i][j]);
		}
		ft_printf("\n");
	}
	//check_map(args, 0, 0);
	
}
