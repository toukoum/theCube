/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:12:08 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/18 11:29:08 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	calculate_height_width_sprite(t_cub *cub, t_sprite *s)
{
	s->spriteHeight = (int)(HWIN / cub->transform.y);
	s->spriteHeight = abs(s->spriteHeight);
	s->drawStart.y = -s->spriteHeight / 2 + HWIN / 2;
	if (s->drawStart.y < 0)
		s->drawStart.y = 0;
	s->drawEnd.y = s->spriteHeight / 2 + HWIN / 2;
	if (s->drawEnd.y >= HWIN)
		s->drawEnd.y = HWIN - 1;
	s->spriteScreenX = (int)((WWIN / 2) * (1 + cub->transform.x
				/ cub->transform.y));
	s->spriteWidth = (HWIN / (cub->transform.y));
	s->drawStart.x = -s->spriteWidth / 2 + s->spriteScreenX;
	if (s->drawStart.x < 0)
		s->drawStart.x = 0;
	s->drawEnd.x = s->spriteWidth / 2 + s->spriteScreenX;
	if (s->drawEnd.x >= WWIN)
		s->drawEnd.x = WWIN - 1;
}

/**
 * pour chaque bande, on dessine les pixel de haut
 * en bas.
 * il faut remaper y dans [0, tex.height] pour avoir
 * tex_y et comme ca on sait tex_x et tex_y et on a
 * plus qu'a recup la couleur, en ne dessinant
 * pas la couleur de fond du sprite (noir ici)
 *
 * d correspond a  position relative en pixels dans la texture,
 * prenant en compte la taille du sprite et la
 * position actuelle sur l'écran.
 */
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
		tex_y = ((d * sprite->texture.height) / sprite->spriteHeight) / 256;
		pixel_index = ((int)tex_y * sprite->texture.line_length)
			+ ((int)sprite->texX * (sprite->texture.bits_per_pixel / 8));
		color = *(int *)(sprite->texture.addr + pixel_index);
		if (color & 0x00FFFFFF)
			my_mlx_pixel_put(&cub->img, x, y, color);
		y++;
	}
}

/**
 * @brief a partir de x (current stripe), avoir la coordonee x
 * de la bande de texture a dessiner.
 * par ex: pour une bande a dessiner de x = 450, il faudrait
 * utiliser le pixel 64 de la texture (en x)
 */
void	get_tex_x(t_sprite *sprite, int x)
{
	sprite->texX = (256 * (x - (-sprite->spriteWidth / 2
					+ sprite->spriteScreenX)) * sprite->texture.width
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
			get_tex_x(sprite, x);
			draw_pixel_sprite(cub, sprite, x);
		}
		x++;
	}
}

/**
 * @brief on affiche les sprites du plus

	* loin au plus proche (dist_player_sprites
	* contient les sprites triés par ordre decroissant)
 */
void	draw_sprites(t_cub *cub)
{
	int			i;
	t_sprite	sprit;

	i = 0;
	while (i < NSPRITE)
	{
		sprit = cub->sprites[(int)cub->dist_ps[i][0]];
		if (sprit.play)
			sprit.texture = cub->sprites_textures[sprit.idx_textures]
			[cub->frame_sprite % sprit.nframe];
		else
			sprit.texture = cub->sprites_textures[sprit.idx_textures][0];
		calculate_pos_relative_sprite(i, cub);
		calculate_height_width_sprite(cub, &sprit);
		draw_column_sprite(cub, &sprit);
		i++;
	}
}
