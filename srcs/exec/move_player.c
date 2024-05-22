/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:23:53 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/22 19:43:31 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

static void	rotate_right(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_r;
	double	sin_r;

	cos_r = cos(cub->rotSpeed);
	sin_r = sin(cub->rotSpeed);
	old_dir_x = cub->dir.x;
	cub->dir.x = cub->dir.x * cos_r - cub->dir.y * sin_r;
	cub->dir.y = old_dir_x * sin_r + cub->dir.y * cos_r;
	old_plane_x = cub->plane.x;
	cub->plane.x = cub->plane.x * cos_r - cub->plane.y * sin_r;
	cub->plane.y = old_plane_x * sin_r + cub->plane.y * cos_r;
}

void	rotate_player(int keycode, t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_r;
	double	sin_r;

	cos_r = cos(-cub->rotSpeed);
	sin_r = sin(-cub->rotSpeed);
	if (keycode == XK_Left)
	{
		old_dir_x = cub->dir.x;
		cub->dir.x = cub->dir.x * cos_r - cub->dir.y * sin_r;
		cub->dir.y = old_dir_x * sin_r + cub->dir.y * cos_r;
		old_plane_x = cub->plane.x;
		cub->plane.x = cub->plane.x * cos_r - cub->plane.y * sin_r;
		cub->plane.y = old_plane_x * sin_r + cub->plane.y * cos_r;
	}
	else
		rotate_right(cub);
}

static void	add_move(t_cub *cub, int keycode, t_coord *next)
{
	if (keycode == XK_w)
	{
		next->x += MOVESPEED * cub->dir.x;
		next->y += MOVESPEED * cub->dir.y;
	}
	else if (keycode == XK_s)
	{
		next->x -= MOVESPEED * cub->dir.x;
		next->y -= MOVESPEED * cub->dir.y;
	}
	else if (keycode == XK_d)
	{
		next->x -= MOVESPEED * cub->dir.y;
		next->y += MOVESPEED * cub->dir.x;
	}
	else if (keycode == XK_a)
	{
		next->x += MOVESPEED * cub->dir.y;
		next->y -= MOVESPEED * cub->dir.x;
	}
}

bool	is_door_open(char **map, int x, int y, t_door **doors)
{
	int	i;

	i = 0;
	if (map[y][x] == 'D')
	{
		while (doors[i])
		{
			if (doors[i]->pos.x == x && doors[i]->pos.y == y
				&& doors[i]->is_open)
				return (true);
			i++;
		}
	}
	return (false);
}

/**
 * @brief a finir
 */
void	move_player(int keycode, t_cub *cub)
{
	t_coord		next;
	t_int_coord	map_index;

	next.x = cub->player.x;
	next.y = cub->player.y;
	add_move(cub, keycode, &next);
	map_index.x = (int)(next.x);
	map_index.y = (int)(next.y);
	if (cub->map->map[map_index.y][map_index.x] == '0'
		|| cub->map->map[map_index.y][map_index.x] == cub->player.start_angle)
	{
		cub->player.x = next.x;
		cub->player.y = next.y;
	}
	// else
	//	printf("Movement blocked at (%d, %d) %f, %f\n", map_index.x,
	//		map_index.y, next.x, next.y);
}
