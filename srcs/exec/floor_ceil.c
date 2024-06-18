/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:29:18 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/18 11:48:57 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	init_rayf(t_cub *cub, t_rayfloor *rayf)
{
	rayf->raydir0.x = cub->dir.x - cub->plane.x;
	rayf->raydir0.y = cub->dir.y - cub->plane.y;
	rayf->raydir1.x = cub->dir.x + cub->plane.x;
	rayf->raydir1.y = cub->dir.y + cub->plane.y;
	rayf->posz = HWIN / 2;
}

void	draw_pixel_floor(t_cub *cub, t_rayfloor *rayf, t_img *texture)
{
	unsigned int	color;
	int				pixel_idx;
	t_int_coord		tex;

	rayf->cell.x = (int)rayf->floor.x / 2;
	rayf->cell.y = (int)rayf->floor.y / 2;
	tex.x = (int)(texture->width * (rayf->floor.x / 2 - rayf->cell.x));
	tex.y = (int)(texture->height * (rayf->floor.y / 2 - rayf->cell.y));
	tex.x %= texture->width;
	tex.y %= texture->height;
	pixel_idx = tex.y * texture->line_length + (tex.x * (texture->bits_per_pixel
				/ 8));
	if (pixel_idx < 0)
		pixel_idx = 0;
	color = *(int *)(texture->addr + pixel_idx);
	my_mlx_pixel_put(&cub->img, rayf->idx.x, rayf->idx.y, color);
}

void	raycast_floor(t_cub *cub, t_rayfloor *rayf)
{
	t_int_coord	idx;

	idx.y = HWIN / 2;
	while (idx.y < HWIN)
	{
		rayf->p = idx.y - (HWIN / 2);
		if (rayf->p == 0)
			rayf->p = 1;
		rayf->rowdist = rayf->posz / rayf->p;
		rayf->d.x = rayf->rowdist * (rayf->raydir1.x - rayf->raydir0.x) / WWIN;
		rayf->d.y = rayf->rowdist * (rayf->raydir1.y - rayf->raydir0.y) / WWIN;
		rayf->floor.x = cub->player.x + rayf->rowdist * rayf->raydir0.x;
		rayf->floor.y = cub->player.y + rayf->rowdist * rayf->raydir0.y;
		idx.x = -1;
		while (idx.x++ < WWIN - 1)
		{
			rayf->idx = idx;
			draw_pixel_floor(cub, rayf, &cub->sky);
			rayf->idx.y = HWIN - rayf->idx.y - 1;
			draw_pixel_floor(cub, rayf, &cub->ground);
			rayf->floor.x += rayf->d.x;
			rayf->floor.y += rayf->d.y;
		}
		idx.y++;
	}
}

void	draw_simple_floor_ceil(t_cub *cub)
{
	t_int_coord	idx;

	idx.y = 0;
	while (idx.y < HWIN)
	{
		idx.x = 0;
		while (idx.x < WWIN)
		{
			if (idx.y < HWIN / 2)
				my_mlx_pixel_put(&cub->img, idx.x, idx.y,
					cub->map->ceil_col.color);
			else
				my_mlx_pixel_put(&cub->img, idx.x, idx.y,
					cub->map->floor_col.color);
			idx.x++;
		}
		idx.y++;
	}
}

void	draw_floor_ceil(t_cub *cub)
{
	t_rayfloor	rayf;

	if (!cub->map->is_floor_texture)
		return (draw_simple_floor_ceil(cub));
	init_rayf(cub, &rayf);
	raycast_floor(cub, &rayf);
}
