/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:48:01 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/29 00:10:07 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	drawTile(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TSIZE)
	{
		j = 0;
		while (j < TSIZE)
		{
			my_mlx_pixel_put(&cub->mmap, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

int	getPixelColor(char **map, t_int_coord *mapIndex)
{
	if (!map[mapIndex->y] || !map[mapIndex->y][mapIndex->x]
		|| is_space(map[mapIndex->y][mapIndex->x]))
		return (CUNDEFINED);
	if (map[mapIndex->y][mapIndex->x] == '1')
		return (CWALL);
	else if (map[mapIndex->y][mapIndex->x] == '0')
	{
		return (CGROUND);
	}
	else
		return (CLIME);
}

void	drawBorder(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < HMAP)
	{
		x = 0;
		while (x < WMAP)
		{
			if (y == 0 || y == HMAP - 1 || x == 0 || x == WMAP - 1)
				my_mlx_pixel_put(&cub->mmap, x, y, CWALL);
			x++;
		}
		y++;
	}
}

void	drawLineMap(t_img *img, t_coord x1, t_coord x2, int color)
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
	while (i <= dmax && i < WMAP / 2)
	{
		my_mlx_pixel_put(img, (int)x1.x, (int)x1.y, color);
		x1.x += increment.x;
		x1.y += increment.y;
		i++;
	}
}

void	drawLine(t_img *img, t_coord x1, t_coord x2, int color)
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
		my_mlx_pixel_put(img, (int)x1.x, (int)x1.y, color);
		x1.x += increment.x;
		x1.y += increment.y;
		i++;
	}
}
