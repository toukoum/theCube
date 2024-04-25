/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util2_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:14:51 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/25 18:32:58 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	goto_next_char(int *i, char *line)
{
	while (is_space(line[*i]))
		(*i)++;
}


void	goto_next_char_sizet(size_t *i, char *line)
{
	while (is_space(line[*i]))
		(*i)++;
}

/**
 * @brief atoi for check if number is in range
 *
 * 		=> 0 to 255 max
 * 	err to 1 if overflow
 *
 * @param line
 * @param i
 * @param err
 * @return int
 */
int	min_atoi_boost(char *line, int *i, int *err)
{
	int	result;

	result = 0;
	while (line[*i] && ft_isdigit(line[*i]) && result <= 255)
	{
		result = result * 10 + (line[*i] - '0');
		(*i)++;
	}
	if (result > 255 || (!is_space(line[*i]) && line[*i] != ','))
		*err = 1;
	return (result);
}

bool	is_texture_id(char *line, int i)
{
	return (!ft_strncmp(line + i, "NO", 2) || !ft_strncmp(line + i, "SO", 2)
		|| !ft_strncmp(line + i, "WE", 2) || !ft_strncmp(line + i, "EA", 2));
}
