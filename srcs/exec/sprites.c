/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:56:23 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/25 13:02:04 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

/**
 * @brief calcul de la distance de chaque sprites avec
 * la pos du player
 *
 * dist_player_sprites[NSPRITE][2];
 *
 * a l'index 0, index du sprite
 * a l'index 1, distance entre ce sprite et le player
 */
void	store_dist_player_sprites(t_cub *cub)
{
	int	i;
	t_sprite sprite;

	i = 0;
	while (i < NSPRITE)
	{
		sprite = cub->sprites[i];
		cub->dist_ps[i][0] = i;
		cub->dist_ps[i][1] = (cub->player.x - sprite.sprite_pos.x)
			* (cub->player.x - sprite.sprite_pos.x) + (cub->player.y
				- sprite.sprite_pos.y) * (cub->player.y
				- sprite.sprite_pos.y);
		i++;
	}
	sort_dist_player_sprites(cub->dist_ps);
}

/**
 *
 * @param cub
 */
void	sprites(t_cub *cub)
{
	cub->invMatriceCam = 1.0 / (cub->plane.x * cub->dir.y - cub->dir.x
		* cub->plane.y);
	store_dist_player_sprites(cub);
	draw_sprites(cub);
}
