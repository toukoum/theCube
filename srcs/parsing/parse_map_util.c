/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:09:26 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/25 14:59:09 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

bool	valid_value_map(char c, bool space)
{
	if (space)
	{
		return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
			|| is_space(c));
	}
	else
	{
		return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
	}
		
}

void	get_line_width(t_args *args, char *line)
{
	int		i;
	int	result;
	bool	found_map;
	
	found_map = false;
	result = 0;
	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]) || !found_map)
			result++;
		if (!valid_value_map(line[i], true))
			return (free(line), exit_parse_map(args, INVALID_CHARACTER, true));
		if (valid_value_map(line[i], false) && !found_map)
			found_map = true;
		i++;
	}
	if (result > args->width)
		args->width = result;
}

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			return (false);
		i++;
	}
	return (true);
}

void	str_copy_cube(char *dst, char *src)
{
	int	i;
	int	j;
	bool found_map;

	found_map = false;
	j = 0;
	i = 0;
	while (src[i])
	{	
		if (!is_space(src[i]) || !found_map)
			dst[j++] = src[i];
		if (valid_value_map(src[i], false) && !found_map)
			found_map = true;
		i++;
	}
}
