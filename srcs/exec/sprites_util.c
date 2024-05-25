/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:13:20 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/25 12:39:45 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	sort_dist_player_sprites(double dist_ps[NSPRITE][2])
{
	double	tmp_dist;
	double	tmp_index;

	int i, j;
	i = 0;
	while (i < NSPRITE)
	{
		j = 0;
		while (j < NSPRITE - i - 1)
		{
			if (dist_ps[j][1] < dist_ps[j + 1][1])
			{
				tmp_dist = dist_ps[j][1];
				dist_ps[j][1] = dist_ps[j + 1][1];
				dist_ps[j + 1][1] = tmp_dist;
				tmp_index = dist_ps[j][0];
				dist_ps[j][0] = dist_ps[j + 1][0];
				dist_ps[j + 1][0] = tmp_index;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief
 * todo, check pour voir a travers les murs
 */
bool	is_sprite_viewable(t_cub *cub, int x)
{
	return (cub->transform.y > 0 && x > 0 && x < WWIN
		&& cub->transform.y <= cub->wallDist[x]);
}

void	init_pos_sprite(t_cub *cub)
{
	cub->sprite_pos[0].x = 1.5;
	cub->sprite_pos[0].y = 1.5;
	cub->idx_textures_sprites[0] = 0;
	cub->sprite_pos[1].x = 4.5;
	cub->sprite_pos[1].y = 2.5;
	cub->idx_textures_sprites[1] = 1;
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
	sprite.x = cub->sprite_pos[isprite].x - cub->player.x;
	sprite.y = cub->sprite_pos[isprite].y - cub->player.y;
	cub->transform.x = cub->dir.y * sprite.x - cub->dir.x * sprite.y;
	cub->transform.y = -cub->plane.y * sprite.x + cub->plane.x * sprite.y;
	cub->transform.x *= cub->invMatriceCam;
	cub->transform.y *= cub->invMatriceCam;
}
