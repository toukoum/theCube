/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_minimap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:45:44 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/29 00:10:59 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	initRayStep(t_ray *ray, t_cub *cub)
{
	if (ray->rayDir.x < 0)
	{
		ray->step.x = -1;
		ray->sideDist.x = (cub->player.x - ray->map.x) * ray->d.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sideDist.x = (ray->map.x + 1 - cub->player.x) * ray->d.x;
	}
	if (ray->rayDir.y < 0)
	{
		ray->step.y = -1;
		ray->sideDist.y = (cub->player.y - ray->map.y) * ray->d.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sideDist.y = (ray->map.y + 1 - cub->player.y) * ray->d.y;
	}
}

void	initRay(t_cub *cub, t_ray *ray, double camX)
{
	ray->rayDir.x = cub->dir.x + camX * cub->plane.x;
	ray->rayDir.y = cub->dir.y + camX * cub->plane.y;
	ray->map.x = (int)cub->player.x;
	ray->map.y = (int)cub->player.y;
	if (ray->rayDir.x == 0)
		ray->d.x = INFINITY;
	else
		ray->d.x = fabs(1 / ray->rayDir.x);
	if (ray->rayDir.y == 0)
		ray->d.y = INFINITY;
	else
		ray->d.y = fabs(1 / ray->rayDir.y);
	ray->hit = false;
	initRayStep(ray, cub);
}

void	dda(t_ray *ray, char **map)
{
	while (!ray->hit)
	{
		if (ray->sideDist.x < ray->sideDist.y)
		{
			ray->sideDist.x += ray->d.x;
			ray->map.x += ray->step.x;
			ray->side_hit = false;
		}
		else
		{
			ray->sideDist.y += ray->d.y;
			ray->map.y += ray->step.y;
			ray->side_hit = true;
		}
		if (map[ray->map.y][ray->map.x] == '1')
			ray->hit = true;
	}
	if (ray->side_hit)
		ray->perpWallDist = ray->sideDist.y - ray->d.y;
	else
		ray->perpWallDist = ray->sideDist.x - ray->d.x;
}

int		getWallColor(t_int_coord *mapIndex, char **map)
{
	if (!map[mapIndex->y] || !map[mapIndex->y][mapIndex->x]
		|| is_space(map[mapIndex->y][mapIndex->x]))
		return (CRED);
	if (map[mapIndex->y][mapIndex->x] == '1')
		return (CWALL);
	else if (map[mapIndex->y][mapIndex->x] == '0')
	{
		return (CGROUND);
	}
	else
		return (CWHITE);
}
void	drawColumn(int x, t_ray *ray, t_cub *cub)
{
	int	lineHeight;
	int	drawStart;
	int	drawEnd;

	lineHeight = (int)(HWIN / ray->perpWallDist);
	drawStart = -lineHeight / 2 + HWIN / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + HWIN / 2;
	if (drawEnd >= HWIN)
		drawEnd = WWIN - 1;

	drawLine(&cub->img, (t_coord){x, drawStart}, (t_coord){x, drawEnd}, getWallColor(&ray->map, cub->map->map));
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
		// draw the ray
		if (x % 50 == 0)
			drawLineMap(&cub->mmap, (t_coord){WMAP / 2, HMAP / 2}, (t_coord){dist.x,
				dist.y}, CORANGE);
		drawColumn(x, &ray, cub);
		x++;
	}
	// vecteur direction
	drawLineMap(&cub->mmap, (t_coord){WMAP / 2, HMAP / 2}, (t_coord){WMAP / 2 + cub->dir.x
		* TSIZE, HMAP / 2 + cub->dir.y * TSIZE}, CBLUE);
	// vecteur plane
	drawLineMap(&cub->mmap, (t_coord){WMAP / 2 - (cub->plane.x * TSIZE), HMAP / 2
		- (cub->plane.y * TSIZE)}, (t_coord){WMAP / 2 + (cub->plane.x * TSIZE),
		HMAP / 2 + (cub->plane.y * TSIZE)}, CRED);
}
