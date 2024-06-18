/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:13:20 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/18 11:18:16 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	sort_dist_player_sprites(double dist_ps[NSPRITE][2])
{
	double	tmp_dist;
	double	tmp_index;
	int		i;
	int		j;

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

void	init_1_sprite(t_cub *cub)
{
	cub->sprites[0].pos.x = 12.5;
	cub->sprites[0].pos.y = 8.5;
	cub->sprites[0].idx_textures = 0;
	cub->sprites[0].nframe = 24;
	cub->sprites[1].pos.x = 12.5;
	cub->sprites[1].pos.y = 4.5;
	cub->sprites[1].idx_textures = 1;
	cub->sprites[1].nframe = 33;
	cub->sprites[2].pos.x = 16.5;
	cub->sprites[2].pos.y = 1.5;
	cub->sprites[2].idx_textures = 2;
	cub->sprites[2].nframe = 62;
	cub->sprites[3].pos.x = 17.5;
	cub->sprites[3].pos.y = 9.5;
	cub->sprites[3].idx_textures = 3;
	cub->sprites[3].nframe = 40;
	cub->sprites[4].pos.x = 17.5;
	cub->sprites[4].pos.y = 6.5;
	cub->sprites[4].idx_textures = 4;
	cub->sprites[4].nframe = 18;
	cub->sprites[5].pos.x = 9.5;
	cub->sprites[5].pos.y = 9.5;
	cub->sprites[5].idx_textures = 5;
	cub->sprites[5].nframe = 32;
}

void	init_2_sprite(t_cub *cub)
{
	cub->sprites[8].pos.x = 27.5;
	cub->sprites[8].pos.y = 5.5;
	cub->sprites[8].idx_textures = 1;
	cub->sprites[8].nframe = 33;
	cub->sprites[9].pos.x = 26.5;
	cub->sprites[9].pos.y = 5.5;
	cub->sprites[9].idx_textures = 2;
	cub->sprites[9].nframe = 62;
	cub->sprites[10].pos.x = 25.5;
	cub->sprites[10].pos.y = 5.5;
	cub->sprites[10].idx_textures = 3;
	cub->sprites[10].nframe = 40;
	cub->sprites[11].pos.x = 24.5;
	cub->sprites[11].pos.y = 5.5;
	cub->sprites[11].idx_textures = 4;
	cub->sprites[11].nframe = 18;
	cub->sprites[12].pos.x = 24.5;
	cub->sprites[12].pos.y = 4.5;
	cub->sprites[12].idx_textures = 5;
	cub->sprites[12].nframe = 32;
	cub->sprites[13].pos.x = 24.5;
	cub->sprites[13].pos.y = 3.5;
	cub->sprites[13].idx_textures = 6;
	cub->sprites[13].nframe = 42;
	cub->sprites[13].play = true;
}

void	init_pos_sprite(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < NSPRITE)
		cub->sprites[i].play = false;
	init_1_sprite(cub);
	init_2_sprite(cub);
	cub->sprites[6].pos.x = 16.5;
	cub->sprites[6].pos.y = 3.5;
	cub->sprites[6].idx_textures = 6;
	cub->sprites[6].nframe = 42;
	cub->sprites[7].pos.x = 28.5;
	cub->sprites[7].pos.y = 5.5;
	cub->sprites[7].idx_textures = 0;
	cub->sprites[7].nframe = 24;
	cub->sprites[7].play = true;
	cub->sprites[8].play = true;
	cub->sprites[9].play = true;
	cub->sprites[10].play = true;
	cub->sprites[11].play = true;
	cub->sprites[12].play = true;
	i = -1;
	while (++i < NSPRITE)
		cub->map->map[(int)cub->sprites[i].pos.y]
		[(int)cub->sprites[i].pos.x] = '2';
}
