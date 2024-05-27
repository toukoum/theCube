/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:02:12 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/26 17:21:45 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

/**
 * @brief draw the minimap with correct color
 * 	for each pixel of minimap, check if it inside the map.
 * 	pick the correct color accordingly of the pos in the map
 * 	(ground, wall, outside the map, in the map but nothing)
 *
 * @param cub
 * @param player pos in PIXEL of the player
 */
void	draw_minimap(t_cub *cub, t_coord player)
{
	t_coord		map_pos;
	t_int_coord	map_idx;
	int			y;
	int			x;

	y = 0;
	while (y < HMAP)
	{
		x = 0;
		while (x < WMAP)
		{
			map_pos.x = player.x - (WMAP / 2) + x;
			map_pos.y = player.y - (HMAP / 2) + y;
			map_idx.x = map_pos.x / TSIZE;
			map_idx.y = map_pos.y / TSIZE;
			if (map_idx.x < 0 || map_idx.x >= cub->map->width || map_idx.y < 0
				|| map_idx.y >= cub->map->height)
				my_mlx_pixel_put(&cub->mmap, x, y, CUNDEFINED);
			else
				my_mlx_pixel_put(&cub->mmap, x, y,
					get_pixel_color(cub->map->map, &map_idx));
			x++;
		}
		y++;
	}
}

void	draw_player(t_cub *cub)
{
	draw_rect(&cub->mmap, (t_int_coord){WMAP / 2 - 2, HMAP / 2 - 2},
		(t_int_coord){4, 4}, CRED);
}

void	draw_all(t_cub *cub)
{
	draw_minimap(cub, (t_coord){cub->player.x * TSIZE, cub->player.y * TSIZE});
	draw_floor_ceil(cub);
	raycasting(cub);
	draw_border_minimap(cub);
	draw_player(cub);
	sprites(cub);
}
