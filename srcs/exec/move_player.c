/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:23:53 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/14 22:34:17 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

static void	rotate_right(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	// both camera direction and camera plane must be rotated
	old_dir_x = cub->dir.x;
	cub->dir.x = cub->dir.x * cos(ROTSPEED) - cub->dir.y * sin(ROTSPEED);
	cub->dir.y = old_dir_x * sin(ROTSPEED) + cub->dir.y * cos(ROTSPEED);
	old_plane_x = cub->plane.x;
	cub->plane.x = cub->plane.x * cos(ROTSPEED) - cub->plane.y * sin(ROTSPEED);
	cub->plane.y = old_plane_x * sin(ROTSPEED) + cub->plane.y * cos(ROTSPEED);
}

void	rotate_player(int keycode, t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == XK_Left)
	{
		// both camera direction and camera plane must be rotated
		old_dir_x = cub->dir.x;
		cub->dir.x = cub->dir.x * cos(-ROTSPEED) - cub->dir.y * sin(-ROTSPEED);
		cub->dir.y = old_dir_x * sin(-ROTSPEED) + cub->dir.y * cos(-ROTSPEED);
		old_plane_x = cub->plane.x;
		cub->plane.x = cub->plane.x * cos(-ROTSPEED) - cub->plane.y
			* sin(-ROTSPEED);
		cub->plane.y = old_plane_x * sin(-ROTSPEED) + cub->plane.y
			* cos(-ROTSPEED);
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

/**
 * @brief a finir
 */
void	move_player(int keycode, t_cub *cub)
{
	t_coord next;
	t_int_coord map_index;

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
	else
		printf("Movement blocked at (%d, %d) %f, %f\n", map_index.x,
			map_index.y, next.x, next.y);
}
