/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:45:44 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/30 15:05:59 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	draw_column(int x, t_ray *ray, t_cub *cub)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (int)(HWIN / ray->perpWallDist);
	draw_start = -line_height / 2 + HWIN / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HWIN / 2;
	if (draw_end >= HWIN)
		draw_end = HWIN - 1;
	draw_line(&cub->img, (t_coord){x, draw_start}, (t_coord){x, draw_end},
		get_wall_color(&ray->map, cub->map->map, ray->side_hit));
}

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

void	dda(t_ray *ray, char **map)
{
	while (map[ray->map.y][ray->map.x] != '1')
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
	while (x < WWIN)
	{
		// remaper dans -1,1 la coordonne du pixel
		cam_x = 2 * x / (double)WWIN - 1;
		init_ray(cub, &ray, cam_x);
		dda(&ray, cub->map->map);
		dist.x = (WMAP / 2) + ray.rayDir.x * ray.perpWallDist * TSIZE;
		dist.y = (HMAP / 2) + ray.rayDir.y * ray.perpWallDist * TSIZE;


		//calcul for texture
		
		//double offset;
		//if (ray.side_hit == 'N' || ray.side_hit == 'S')
		//	offset = cub->player.y + ray.perpWallDist * ray.rayDir.y;
		//else
		//	offset = cub->player.x + ray.perpWallDist * ray.rayDir.x;
		//offset -= floor(offset);
		
		//int texX = (int)(offset * )



		
		// draw the ray
		if (x % 75 == 0)
			draw_line_minimap(&cub->mmap, (t_coord){WMAP / 2, HMAP / 2},
				(t_coord){dist.x, dist.y}, CORANGE);
		// draw the column
		draw_column(x, &ray, cub);
		x++;
	}
}
