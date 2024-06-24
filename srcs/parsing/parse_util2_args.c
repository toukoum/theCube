/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util2_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:14:51 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/24 13:29:23 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	goto_next_char(int *i, char *line)
{
	if (!line[*i])
		return ;
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
	return ((line[i] == 'N' && line[i + 1] == 'O') || (line[i] == 'S' && line[i
				+ 1] == 'O') || (line[i] == 'W' && line[i + 1] == 'E')
		|| (line[i] == 'E' && line[i + 1] == 'A') || (line[i] == 'G' && line[i
				+ 1] == 'R') || (line[i] == 'S' && line[i + 1] == 'K'));
}
