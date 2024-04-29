/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:02:12 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/29 13:56:42 by rgiraud          ###   ########.fr       */
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
void drawMinimap(t_cub *cub, t_coord player)
{
	t_coord mapPos;
	t_int_coord	mapIndex;
	int		y;
	int		x;
	
	y = 0;
	while (y < HMAP)
	{
		x = 0;
		while (x < WMAP) {
			mapPos.x = player.x - (WMAP / 2) + x;  // Position in pixels
			mapPos.y = player.y - (HMAP / 2) + y;
			mapIndex.x = mapPos.x / TSIZE;  // Convert pixel position to map index
			mapIndex.y = mapPos.y / TSIZE;

			if (mapIndex.x < 0 || mapIndex.x >= cub->map->width || mapIndex.y < 0 || mapIndex.y >= cub->map->height)
				my_mlx_pixel_put(&cub->mmap, x, y, CUNDEFINED);
			else
				my_mlx_pixel_put(&cub->mmap, x, y, getPixelColor(cub->map->map, &mapIndex));
			x++;
    	}
		y++;
	}
}

void drawPlayer(t_cub *cub)
{
	// vecteur direction
	drawLineMinimap(&cub->mmap, (t_coord){WMAP / 2, HMAP / 2}, (t_coord){WMAP / 2
		+ cub->dir.x * TSIZE, HMAP / 2 + cub->dir.y * TSIZE}, CBLUE);
	// vecteur plane
	drawLineMinimap(&cub->mmap, (t_coord){WMAP / 2 - (cub->plane.x * TSIZE), HMAP
		/ 2 - (cub->plane.y * TSIZE)}, (t_coord){WMAP / 2 + (cub->plane.x
			* TSIZE), HMAP / 2 + (cub->plane.y * TSIZE)}, CRED);
	my_mlx_pixel_put(&cub->mmap, WMAP / 2, HMAP / 2, CRED); // player
}
void	drawAll(t_cub *cub)
{
	drawMinimap(cub, (t_coord){cub->player.x * TSIZE, cub->player.y * TSIZE});
	rayCasting(cub);
	drawBorderMinimap(cub);
	drawPlayer(cub);
}
