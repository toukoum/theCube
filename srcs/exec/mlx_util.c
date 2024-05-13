/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:33:58 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/13 12:11:58 by ketrevis         ###   ########.fr       */
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
		cub->plane.x *= (1 + CHANGEFOV);
		cub->plane.y *= (1 + CHANGEFOV);
	}
	else if (keycode == XK_minus)
	{
		cub->plane.x *= (1 - CHANGEFOV);
		cub->plane.y *= (1 - CHANGEFOV);
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
