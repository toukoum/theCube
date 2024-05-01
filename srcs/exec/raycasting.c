/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:45:44 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/01 17:05:28 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	draw_column_texture(t_img *img, t_ray *ray, t_img *texture, int texX)
{
	double	increment_y;
	double	tex_y;
	int		color;
	int		pixel_index;

	increment_y = (double)texture->height / ray->line_height;
	tex_y = (ray->start_point.y - HWIN / 2 + ray->line_height / 2) * increment_y;
	while (ray->start_point.y < ray->end_point.y)
	{
		pixel_index = (((int)tex_y % texture->height) * texture->line_length)
			+ (texX * (texture->bits_per_pixel / 8));
		color = *(int *)(texture->addr + pixel_index);
		my_mlx_pixel_put(img, ray->start_point.x, ray->start_point.y, color);
		tex_y += increment_y;
		ray->start_point.y++;
	}
}

void	draw_column(int x, t_ray *ray, t_cub *cub)
{
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	offset;

	ray->line_height = (int)(HWIN / ray->perpWallDist);
	draw_start = -ray->line_height / 2 + HWIN / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = ray->line_height / 2 + HWIN / 2;
	if (draw_end >= HWIN)
		draw_end = HWIN - 1;
	if (ray->side_hit == 'N' || ray->side_hit == 'S')
		offset = cub->player.x + ray->perpWallDist * ray->rayDir.x;
	else
		offset = cub->player.y + ray->perpWallDist * ray->rayDir.y;
	offset = offset - floor(offset);
	ray->start_point = (t_int_coord){x, draw_start};
	ray->end_point = (t_int_coord){x, draw_end};
	tex_x = (int)(offset * (double)cub->texN.width);
	if(((ray->side_hit == 'N' || ray->side_hit == 'S') && ray->rayDir.y < 0)) 
		tex_x = cub->texN.width - tex_x - 1;
	if(((ray->side_hit == 'E' || ray->side_hit == 'W') && ray->rayDir.x > 0)) 
		tex_x = cub->texN.width - tex_x - 1;
	draw_column_texture(&cub->img, ray, &cub->texN, tex_x);
}

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
		// draw the ray
		if (x % 75 == 0)
			draw_line_minimap(&cub->mmap, (t_coord){WMAP / 2, HMAP / 2},
				(t_coord){dist.x, dist.y}, CORANGE);
		// draw the column
		draw_column(x, &ray, cub);
		x++;
	}
}
