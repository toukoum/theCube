/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:45:44 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/18 11:20:00 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

//// Calculer texY en utilisant texPos, qui est incrémenté par step
//        int texY = (int)texPos & (texture->height - 1);
//        texPos += step;
void	assign_side_hit(t_ray *ray, bool vertical)
{
	if (vertical)
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

bool	is_door(char **map, int x, int y, t_door **doors)
{
	int	i;

	i = 0;
	if (map[y][x] == 'D')
	{
		while (doors[i])
		{
			if (doors[i]->pos.x == x && doors[i]->pos.y == y
				&& !doors[i]->is_open)
				return (true);
			i++;
		}
	}
	return (false);
}

void	dda(t_ray *ray, char **map, t_door **doors)
{
	ray->is_ray_door = false;
	while (map[ray->map.y][ray->map.x] != '1' && !is_door(map, ray->map.x,
			ray->map.y, doors))
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
	}
	if (ray->side_hit == 'N' || ray->side_hit == 'S')
		ray->perpWallDist = ray->sideDist.y - ray->d.y;
	else
		ray->perpWallDist = ray->sideDist.x - ray->d.x;
	if (map[ray->map.y][ray->map.x] == 'D')
		ray->is_ray_door = true;
}

/**
 * @brief calculer pour chaque pixel de la fenetre
 * les coordonne de rayDirX et rayDirY, puis le trace sur la fenetre.
 *
 * @param cub
 */
void	raycasting(t_cub *cub)
{
	int		x;
	double	cam_x;
	t_ray	ray;
	t_coord	dist;

	x = 0;
	ft_bzero(&ray, sizeof(t_ray));
	while (x < WWIN)
	{
		cam_x = 2 * x / (double)WWIN - 1;
		init_ray(cub, &ray, cam_x);
		dda(&ray, cub->map->map, cub->doors);
		assign_ray_dist(x, ray.perpWallDist, cub);
		dist.x = (WMAP / 2) + ray.rayDir.x * ray.perpWallDist * TSIZE;
		dist.y = (HMAP / 2) + ray.rayDir.y * ray.perpWallDist * TSIZE;
		if (x % 75 == 0)
			draw_line_minimap(&cub->mmap, (t_coord){WMAP / 2, HMAP / 2},
				(t_coord){dist.x, dist.y}, CORANGE);
		draw_column(x, &ray, cub);
		x++;
	}
}
