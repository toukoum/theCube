/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:56:23 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/18 19:43:34 by rgiraud          ###   ########.fr       */
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

	i = 0;
	while (i < NSPRITE)
	{
		cub->dist_ps[i][0] = i;
		cub->dist_ps[i][1] = (cub->player.x - cub->sprite_pos[i].x)
			* (cub->player.x - cub->sprite_pos[i].x) + (cub->player.y
				- cub->sprite_pos[i].y) * (cub->player.y
				- cub->sprite_pos[i].y);
		i++;
	}
	sort_dist_player_sprites(cub->dist_ps);
}

void	init_pos_sprite(t_cub *cub)
{
	cub->sprite_pos[0].x = 1.5;
	cub->sprite_pos[0].y = 1.5;
	cub->sprite_pos[0].x = 4.5;
	cub->sprite_pos[0].y = 2.5;
}

/**
 * @brief calculate the position of the sprite
 * de facon relative a la position de la camera
 *
 * i = index du sprite que l'on calcule
 *
 * transformX = invDet * (dirY * spriteX - dirX * spriteY);
 * transformY = invDet * (-planeY * spriteX + planeX * spriteY);
	//this is actually the depth inside the screen, that what Z is in 3D
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
void	calculate_height_width_sprite(t_cub *cub, t_sprite *s)
{
	s->spriteScreenX = (int)((WWIN / 2) * (1 + cub->transform.x / cub->transform.y));
	s->spriteHeight = (int)(HWIN / cub->transform.y);
	s->spriteHeight = abs(s->spriteHeight);
	s->drawStart.y = -s->spriteHeight / 2 + HWIN / 2;
	if (s->drawStart.y < 0)
		s->drawStart.y = 0;
	s->drawEnd.y = s->spriteHeight / 2 + HWIN / 2;
	if (s->drawEnd.y >= HWIN)
		s->drawEnd.y = HWIN - 1;
	s->spriteWidth = (HWIN / (cub->transform.y));
	s->drawStart.x = -s->spriteWidth / 2 + s->spriteScreenX;
	if (s->drawStart.x < 0)
		s->drawStart.x = 0;
	s->drawEnd.x = s->spriteWidth / 2 + s->spriteScreenX;
	if (s->drawEnd.x >= WWIN)
		s->drawEnd.x = WWIN - 1;
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

void	draw_pixel_sprite(t_cub *cub, t_sprite *sprite, int x)
{
	int	y;
	int	d;
	int	tex_y;
	int	pixel_index;
	int	color;

	y = sprite->drawStart.y;
	while (y < sprite->drawEnd.y)
	{
		d = y * 256 - HWIN * 128 + sprite->spriteHeight * 128;
		tex_y = ((d * cub->barrel.height) / sprite->spriteHeight) / 256;
		pixel_index = ((int)tex_y * cub->barrel.line_length)
			+ ((int)sprite->texX * (cub->barrel.bits_per_pixel / 8));
		color = *(int *)(cub->barrel.addr + pixel_index);
		if (color & 0x00FFFFFF)
			my_mlx_pixel_put(&cub->img, x, y, color);
		y++;
	}
}

/**
 * @brief Get the tex x object
 * texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth
		/ spriteWidth) / 256;

 */
void	get_tex_x(t_cub *cub, t_sprite *sprite, int x)
{
	sprite->texX = (256 * (x - (-sprite->spriteWidth / 2
					+ sprite->spriteScreenX)) * cub->barrel.width
			/ sprite->spriteWidth) / 256;
	sprite->texX = (int)(sprite->texX);
}

/**
 * @brief
 * loop through every vertical stripe of the sprite on screen
 */
void	draw_column_sprite(t_cub *cub, t_sprite *sprite)
{
	int	x;

	x = sprite->drawStart.x;
	while (x < sprite->drawEnd.x)
	{
		if (is_sprite_viewable(cub, x))
		{
			get_tex_x(cub, sprite, x);
			draw_pixel_sprite(cub, sprite, x);
		}
		x++;
	}
}

/**
 * @brief on affiche les sprites du plus
 * loin au plus proche (dist_ps contient les sprites triés)
 */
void	draw_sprites(t_cub *cub)
{
	int			i;
	t_sprite	sprit;

	i = 0;
	while (i < NSPRITE)
	{
		calculate_pos_relative_sprite(i, cub);
		calculate_height_width_sprite(cub, &sprit);
		draw_column_sprite(cub, &sprit);
		i++;
	}
}

/**
 *
 * @param cub
 */
void	sprites(t_cub *cub)
{
	init_pos_sprite(cub);
	store_dist_player_sprites(cub);
	draw_sprites(cub);

	// cub->sprite_pos[0][0] = 2;
	// cub->sprite.pos[0][1] = 1;
	// printf("pos of sprites (%d, %d)\n", cub->sprite.pos[0][0],
	// cub->sprite.pos[0][1]);
}