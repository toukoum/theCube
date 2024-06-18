/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:12:08 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/18 11:50:28 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	calculate_height_width_sprite(t_cub *cub, t_sprite *s)
{
	s->spritheight = (int)(HWIN / cub->transform.y);
	s->spritheight = abs(s->spritheight);
	s->drawstart.y = -s->spritheight / 2 + HWIN / 2;
	if (s->drawstart.y < 0)
		s->drawstart.y = 0;
	s->drawend.y = s->spritheight / 2 + HWIN / 2;
	if (s->drawend.y >= HWIN)
		s->drawend.y = HWIN - 1;
	s->spritescrinx = (int)((WWIN / 2) * (1 + cub->transform.x
				/ cub->transform.y));
	s->spritwidth = (HWIN / (cub->transform.y));
	s->drawstart.x = -s->spritwidth / 2 + s->spritescrinx;
	if (s->drawstart.x < 0)
		s->drawstart.x = 0;
	s->drawend.x = s->spritwidth / 2 + s->spritescrinx;
	if (s->drawend.x >= WWIN)
		s->drawend.x = WWIN - 1;
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

	y = sprite->drawstart.y;
	while (y < sprite->drawend.y)
	{
		d = y * 256 - HWIN * 128 + sprite->spritheight * 128;
		tex_y = ((d * sprite->texture.height) / sprite->spritheight) / 256;
		pixel_index = ((int)tex_y * sprite->texture.line_length)
			+ ((int)sprite->texx * (sprite->texture.bits_per_pixel / 8));
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
	sprite->texx = (256 * (x - (-sprite->spritwidth / 2
					+ sprite->spritescrinx)) * sprite->texture.width
			/ sprite->spritwidth) / 256;
	sprite->texx = (int)(sprite->texx);
}

/**
 * @brief
 * loop through every vertical stripe of the sprite on screen
 */
void	draw_column_sprite(t_cub *cub, t_sprite *sprite)
{
	int	x;

	x = sprite->drawstart.x;
	while (x < sprite->drawend.x)
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
