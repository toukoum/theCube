/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:17:08 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/29 13:29:19 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

bool	good_number(int i, char *line)
{
	while (line[i] && line[i] != ',')
	{
		if (!ft_isdigit(line[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	get_number(char *line, int *i, int fd, bool is_last)
{
	int	result;
	int	err;

	err = 0;
	goto_next_char(i, line);
	result = min_atoi_boost(line, i, &err);
	goto_next_char(i, line);
	if (is_last && (line[(*i)] || err))
		return (free(line), close(fd), quit(WRONG_ARG), EXIT_FAILURE);
	else if (!is_last && (line[(*i)] != ',' || err))
		return (free(line), close(fd), quit(WRONG_ARG), EXIT_FAILURE);
	(*i)++;
	return (result);
}

static int rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
void	parse_color_line(t_args *args, char *line, int i)
{
	t_color	tmp_color;
	t_color	*color_target;

	tmp_color.r = get_number(line, &i, args->fd, false);
	tmp_color.g = get_number(line, &i, args->fd, false);
	tmp_color.b = get_number(line, &i, args->fd, true);
	if (line[0] == 'C')
		color_target = &args->ceilColor;
	else
		color_target = &args->floorColor;
	if (color_target->is_correct)
		return (free(line), close(args->fd), quit(CLONE_ARGS));
	*color_target = tmp_color;
	color_target->is_correct = true;
	color_target->color = color_target->r * 1000;
	color_target->color += color_target->g;
	color_target->color = color_target->color * 1000 + color_target->b;
	color_target->color = rgb_to_int(color_target->r, color_target->g, color_target->b);
}
