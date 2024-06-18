/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:33:58 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/18 11:22:17 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	draw_rect(t_img *img, t_int_coord point, t_int_coord dimension,
		int color)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	y = point.y;
	end_x = point.x + dimension.x;
	end_y = point.y + dimension.y;
	while (y < end_y)
	{
		x = point.x;
		while (x < end_x)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	change_fov(t_cub *cub, int keycode)
{
	if (keycode == XK_plus)
	{
		if (!cub->can_move)
			return ;
		cub->can_move = false;
		cub->dir.x *= (1 + CHANGEFOV);
		cub->dir.y *= (1 + CHANGEFOV);
	}
	else if (keycode == XK_minus)
	{
		if (cub->can_move)
			return ;
		cub->can_move = true;
		cub->dir.x /= (1 + CHANGEFOV);
		cub->dir.y /= (1 + CHANGEFOV);
	}
}

void	open_door(t_cub *cub)
{
	int		i;
	double	dist_door_player;

	i = 0;
	while (i < cub->map->ndoor)
	{
		dist_door_player = (cub->player.x - cub->doors[i]->pos.x)
			* (cub->player.x - cub->doors[i]->pos.x) + (cub->player.y
				- cub->doors[i]->pos.y) * (cub->player.y
				- cub->doors[i]->pos.y);
		if (fabs(dist_door_player) < 5.0)
		{
			if ((int)cub->player.x == cub->doors[i]->pos.x
				&& (int)cub->player.y == cub->doors[i]->pos.y)
				return ;
			cub->doors[i]->is_open = !cub->doors[i]->is_open;
		}
		i++;
	}
}

void	draw_line(t_img *img, t_coord x1, t_coord x2, int color)
{
	t_coord	d;
	t_coord	increment;
	double	dmax;
	int		i;

	d.x = x2.x - x1.x;
	d.y = x2.y - x1.y;
	if (fabs(d.x) > fabs(d.y))
		dmax = fabs(d.x);
	else
		dmax = fabs(d.y);
	increment.x = d.x / dmax;
	increment.y = d.y / dmax;
	i = 0;
	dmax = (int)dmax;
	while (i <= dmax)
	{
		if (x1.x > 0 && x1.y > 0)
			my_mlx_pixel_put(img, (int)x1.x, (int)x1.y, color);
		x1.x += increment.x;
		x1.y += increment.y;
		i++;
	}
}
