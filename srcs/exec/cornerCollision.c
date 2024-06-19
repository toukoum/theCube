/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cornerCollision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:05:19 by ketrevis          #+#    #+#             */
/*   Updated: 2024/06/19 11:07:33 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

enum e_direction	get_direction(t_int_coord *player, t_int_coord *next)
{
	if (next->x == player->x - 1 && next->y == player->y - 1)
		return (UP_LEFT);
	else if (next->x == player->x + 1 && next->y == player->y - 1)
		return (UP_RIGHT);
	else if (next->x == player->x - 1 && next->y == player->y + 1)
		return (DOWN_LEFT);
	else if (next->x == player->x + 1 && next->y == player->y + 1)
		return (DOWN_RIGHT);
	return (-1);
}

// true if collided in corner
bool	corner_collision(t_cub *cub, t_int_coord next)
{
	t_int_coord			player;
	enum e_direction	direction;

	player = (t_int_coord){(int)cub->player.x, (int)cub->player.y};
	if (next.x == player.x && next.y == player.y)
		return (false);
	direction = get_direction(&player, &next);
	if (direction == UP_LEFT && cub->map->map[player.y][player.x - 1] == '1'
		&& cub->map->map[player.y - 1][player.x] == '1')
		return (true);
	if (direction == UP_RIGHT && cub->map->map[player.y][player.x + 1] == '1'
		&& cub->map->map[player.y - 1][player.x] == '1')
		return (true);
	if (direction == DOWN_LEFT && cub->map->map[player.y][player.x - 1] == '1'
		&& cub->map->map[player.y + 1][player.x] == '1')
		return (true);
	if (direction == DOWN_RIGHT && cub->map->map[player.y][player.x + 1] == '1'
		&& cub->map->map[player.y + 1][player.x] == '1')
		return (true);
	return (false);
}
