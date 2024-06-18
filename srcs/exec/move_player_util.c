/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:20:47 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/18 11:52:18 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

int	handle_mouse_click(int keycode, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (keycode == 1)
	{
		change_fov(cub, XK_plus);
	}
	else if (keycode == 3)
	{
		change_fov(cub, XK_minus);
	}
	return (ALL_GOOD);
}

/**
 * @brief calculate the position of the sprite
 * de facon relative a la position de la camera
 *
 * i = index du sprite que l'on calcule
 *
 * transformX = invDet * (dirY * spriteX - dirX * spriteY);
 * transformY = invDet * (-planeY * spriteX + planeX * spriteY);
 * transformY est la profondeur du sprite cela correspond a z en 3d
 * transformX est la position x du sprite dans l'espace de la camera
 */

void	calculate_pos_relative_sprite(int i, t_cub *cub)
{
	int		isprite;
	t_coord	sprite;

	isprite = cub->dist_ps[i][0];
	sprite.x = cub->sprites[isprite].pos.x - cub->player.x;
	sprite.y = cub->sprites[isprite].pos.y - cub->player.y;
	cub->transform.x = cub->dir.y * sprite.x - cub->dir.x * sprite.y;
	cub->transform.y = -cub->plane.y * sprite.x + cub->plane.x * sprite.y;
	cub->transform.x *= cub->inv_matrice;
	cub->transform.y *= cub->inv_matrice;
}

bool	is_door_close(char **map, int x, int y, t_door **doors)
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
