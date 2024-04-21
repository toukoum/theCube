/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:09:26 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/21 11:05:24 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

bool	valid_value_map(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| is_space(c));
}

void	get_line_width(t_args *args, char *line)
{
	int		i;
	size_t	result;

	result = 0;
	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			result++;
		if (!valid_value_map(line[i]))
			return (free(line), exit_parse_map(args, INVALID_CHARACTER, true));
		i++;
	}
	if (result > args->width)
		args->width = result;
}

bool	is_empty_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			return (false);
		i++;
	}
	return (true);
}

void str_copy_cube(char *dst, char *src)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (src[i])
	{
		if (!is_space(src[i]))
			dst[j++] = src[i];
		i++;
	}
}