/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:23:01 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/19 16:26:21 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	get_dimensions_map(t_args *args, char *line)
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

void	init_door(t_args *args)
{
	int	i;

	i = 0;
	args->doors = malloc((args->ndoor + 1) * sizeof(t_door *));
	if (!args->doors)
		return (free_all_map(args, MALLOC_ERROR));
	args->doors[args->ndoor] = NULL;
	while (i < args->ndoor)
	{
		args->doors[i] = malloc(sizeof(t_door));
		if (!args->doors[i])
			return (free_all_map(args, MALLOC_ERROR));
		i++;
	}
}

/**
 * @brief args are correct
 * need to check and store map
 * if any pb
 * 	-> close(fd)
 *  -> free(all args.path)
 *
 *  need to free line
 */
void	parse_map(t_args *args, char *line)
{
	char	c;

	c = 'a';
	get_dimensions_map(args, line);
	init_door(args);
	store_map(args);
	args->ndoor = 0;
	check_map(args, 0, 0, c);
	if (!args->is_correct_pos)
		return (free_all_map(args, NO_PLAYER));
}
