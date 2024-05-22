/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:58:13 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/22 19:11:56 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	init_ray_step(t_ray *ray, t_cub *cub)
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

void	init_ray(t_cub *cub, t_ray *ray, double camX)
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
	init_ray_step(ray, cub);
}

int	get_wall_color(t_int_coord *mapIndex, char **map, int side_hit)
{
	if (!map[mapIndex->y] || !map[mapIndex->y][mapIndex->x]
		|| is_space(map[mapIndex->y][mapIndex->x]))
		return (CRED);
	if (map[mapIndex->y][mapIndex->x] == '1')
	{
		if (side_hit == 'N')
			return (CRED);
		else if (side_hit == 'S')
			return (CCYAN);
		else if (side_hit == 'E')
			return (CGREEN);
		else
			return (CYELLOW);
	}
	else if (map[mapIndex->y][mapIndex->x] == '0')
	{
		return (CGROUND);
	}
	else
		return (CWHITE);
}

void assign_ray_dist(int x, double dist, t_cub* cub)
{
	cub->wallDist[x] = dist;
}
