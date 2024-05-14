/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture_wall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:46:18 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/14 13:48:21 by rgiraud          ###   ########.fr       */
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
	tex_y = (ray->start_point.y - HWIN / 2 + ray->line_height / 2)
		* increment_y;
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

static t_img	*get_texture(t_cub *cub, t_ray *ray)
{
	if (ray->side_hit == 'N')
		return (&cub->texN);
	if (ray->side_hit == 'S')
		return (&cub->texS);
	if (ray->side_hit == 'E')
		return (&cub->texE);
	if (ray->side_hit == 'W')
		return (&cub->texW);
	return (NULL);
}

void	get_draw_start_end(t_ray *ray)
{
	ray->draw_start = -ray->line_height / 2 + HWIN / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HWIN / 2;
	if (ray->draw_end >= HWIN)
		ray->draw_end = HWIN - 1;
	ray->line_height = (int)(HWIN / ray->perpWallDist);
}

void	get_offset_tex_x(t_cub *cub, t_ray *ray)
{
	if (ray->side_hit == 'N' || ray->side_hit == 'S')
		ray->offset = cub->player.x + ray->perpWallDist * ray->rayDir.x;
	else
		ray->offset = cub->player.y + ray->perpWallDist * ray->rayDir.y;
	ray->offset = ray->offset - floor(ray->offset);
	ray->tex_x = (int)(ray->offset * (double)ray->texture->width);
	if (((ray->side_hit == 'N' || ray->side_hit == 'S') && ray->rayDir.y < 0))
		ray->tex_x = ray->texture->width - ray->tex_x - 1;
	if (((ray->side_hit == 'E' || ray->side_hit == 'W') && ray->rayDir.x > 0))
		ray->tex_x = ray->texture->width - ray->tex_x - 1;
}

void	draw_column(int x, t_ray *ray, t_cub *cub)
{
	ray->texture = get_texture(cub, ray);
	get_draw_start_end(ray);
	get_offset_tex_x(cub, ray);
	ray->start_point = (t_int_coord){x, ray->draw_start};
	ray->end_point = (t_int_coord){x, ray->draw_end};
	draw_column_texture(&cub->img, ray, ray->texture, ray->tex_x);
}
