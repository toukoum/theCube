/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:45:44 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/29 14:07:32 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	drawColumn(int x, t_ray *ray, t_cub *cub)
{
	int	lineHeight;
	int	drawStart;
	int	drawEnd;

	x = WWIN - x;
	lineHeight = (int)(HWIN / ray->perpWallDist);
	drawStart = -lineHeight / 2 + HWIN / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + HWIN / 2;
	if (drawEnd >= HWIN)
		drawEnd = WWIN - 1;
	drawLine(&cub->img, (t_coord){x, drawStart}, (t_coord){x, drawEnd},
		getWallColor(&ray->map, cub->map->map, ray->side_hit));
}

void	assign_side_hit(t_ray *ray, bool horizontal)
{
	if (horizontal)
	{
		if (ray->step.x > 0)
			ray->side_hit = 'E';
		else
			ray->side_hit = 'W';
	}
	else
	{
		if (ray->step.y > 0)
			ray->side_hit = 'N';
		else
			ray->side_hit = 'S';
	}
}

void	dda(t_ray *ray, char **map)
{
	while (!ray->hit)
	{
		if (ray->sideDist.x < ray->sideDist.y)
		{
			ray->sideDist.x += ray->d.x;
			ray->map.x += ray->step.x;
			assign_side_hit(ray, true);
		}
		else
		{
			ray->sideDist.y += ray->d.y;
			ray->map.y += ray->step.y;
			assign_side_hit(ray, false);
		}
		if (map[ray->map.y][ray->map.x] == '1')
			ray->hit = true;
	}
	if (ray->side_hit == 'N' || ray->side_hit == 'S')
		ray->perpWallDist = ray->sideDist.y - ray->d.y;
	else
		ray->perpWallDist = ray->sideDist.x - ray->d.x;
}

/**
 * @brief calculer pour chaque pixel de la fenetre
 * les coordonne de rayDirX et rayDirY, puis le trace sur la fenetre.
 *
 * @param cub
 */
void	rayCasting(t_cub *cub)
{
	int		x;
	double	camX;
	t_ray	ray;
	t_coord	dist;

	x = 0;
	while (x < WWIN)
	{
		// remaper dans -1,1 la coordonne du pixel
		camX = 2 * x / (double)WWIN - 1;
		initRay(cub, &ray, camX);
		dda(&ray, cub->map->map);
		dist.x = (WMAP / 2) + ray.rayDir.x * ray.perpWallDist * TSIZE;
		dist.y = (HMAP / 2) + ray.rayDir.y * ray.perpWallDist * TSIZE;
		//// draw the ray
		if (x % 75 == 0)
			drawLineMinimap(&cub->mmap, (t_coord){WMAP / 2, HMAP / 2},
				(t_coord){dist.x, dist.y}, CORANGE);
		drawColumn(x, &ray, cub);
		x++;
	}
}
