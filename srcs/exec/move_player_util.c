/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:12:21 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/25 18:24:08 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

bool	perform_collision(t_cub *cub, t_int_coord idx, t_int_coord end,
		t_coord *next)
{
	t_coord	d;

	while (idx.y <= end.y)
	{
		if (cub->map->map[idx.y][idx.x] == '1' || cub->map->map[idx.y][idx.x] == '2' || is_door_close(cub->map->map,
				idx.x, idx.y, cub->doors))
		{
			d.x = next->x - (idx.x + 0.5);
			d.y = next->y - (idx.y + 0.5);
			if (d.x * d.x + d.y * d.y < HITBOX_RADIUS * HITBOX_RADIUS)
				return (true);
		}
		idx.y++;
	}
	return (false);
}
bool	is_collision(t_cub *cub, t_coord *next)
{
	t_int_coord	start;
	t_int_coord	end;
	t_int_coord idx;

	idx.x = 0;
	idx.y = 0;
	start.x = (int)(next->x - HITBOX_RADIUS);
	end.x = (int)(next->x + HITBOX_RADIUS);
	start.y = (int)(next->y - HITBOX_RADIUS);
	end.y = (int)(next->y + HITBOX_RADIUS);
	idx.x = start.x;
	while (idx.x <= end.x)
	{
		idx.y = start.y;
		if (perform_collision(cub, idx, end, next))
		{
			return (true);
		}
		idx.x++;
	}
	return (false);
}
