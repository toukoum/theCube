/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:02:12 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/26 11:13:04 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void drawTile(t_cub * cub, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < TSIZE)
	{
		j = 0;
		while (j < TSIZE)
		{
			my_mlx_pixel_put(&cub->mmap, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

int getPixelColor(char **map, int mapPosX, int mapPosY)
{
	if (!map[mapPosY] || !map[mapPosY][mapPosX] || is_space(map[mapPosY][mapPosX])) // dans la map mais a l'exterieur
		return (CWTF);
	if (map[mapPosY][mapPosX] == '1')
		return (CWALL);
	else if (map[mapPosY][mapPosX] == '0')
	{
		return (CGROUND);
	}
	else
		return (CLIME);
}

void drawBorder(t_cub *cub)
{
	int x;
	int y;

	y = 0;
	while (y < HMAP)
	{
		x = 0;
		while (x < WMAP)
		{
			if (y == 0 || y == HMAP - 1 || x == 0 || x == WMAP - 1)
				my_mlx_pixel_put(&cub->mmap, x, y, CWHITE);
			x++;
		}
		y++;
	}
	
}
void	minimap(t_cub *cub, double playerX, double playerY)
{
	double	mapPosX;
	double	mapPosY;
	int		y;
	int		x;

	y = 0;
	while (y < HMAP)
	{
		x = 0;
		while (x < WMAP) {
			mapPosX = playerX - (WMAP / 2) + x;  // Position in pixels
			mapPosY = playerY - (HMAP / 2) + y;
			int mapIndexX = mapPosX / TSIZE;  // Convert pixel position to map index
			int mapIndexY = mapPosY / TSIZE;

			if (mapIndexX < 0 || mapIndexX >= cub->map->width || mapIndexY < 0 || mapIndexY >= cub->map->height)
				my_mlx_pixel_put(&cub->mmap, x, y, CUNDEFINED);
			else
				my_mlx_pixel_put(&cub->mmap, x, y, getPixelColor(cub->map->map, mapIndexX, mapIndexY));
			x++;
    	}
		y++;
	}
	drawTile(cub, WMAP / 2, HMAP / 2, CPLAYER);
	drawBorder(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mmap.img, 20, 20);
}
