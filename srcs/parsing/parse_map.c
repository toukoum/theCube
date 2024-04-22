/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:23:01 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/22 23:29:55 by rgiraud          ###   ########.fr       */
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
	size_t	i;
	size_t	j;

	i = 0;
	get_dimensions(args, line);
	store_map(args);
	check_map(args, 0, 0);
	if (DEBUG)
	{
		ft_printf("\n===== DEBUG MODE ====\n\n");
		ft_printf("> height/width of map: %d, %d\n", args->height, args->width);
		ft_printf("> pos of player (x, y): %d, %d\n", args->pos_x, args->pos_y);
		ft_printf("> map color floor (r, g, b): %u, %u, %u\n", args->floorColor.r,
			args->floorColor.g, args->floorColor.b);
		ft_printf("> map color ceiling (r, g, b): %u, %u, %u\n",
			args->ceilColor.r, args->ceilColor.g, args->ceilColor.b);
		ft_printf("> map: \n\n");
		while (i < args->height)
		{
			j = 0;
			while (args->map[i][j])
				ft_printf("%c", args->map[i][j++]);
			ft_printf("\n");
			i++;
		}
		ft_printf("\n");
	}
	if (!args->is_correct_pos)
		return (free_all_map(args, NO_PLAYER));
}
