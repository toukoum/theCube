/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:12:28 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/19 11:04:48 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

/**
 * @brief init texture with xpm to file for correct texture
 *
 * @return true if all ok
 * @return false if any error appear
 */
bool	init_texture(void *mlx, char *path, t_img *texture)
{
	texture->img = mlx_xpm_file_to_image(mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
		return (false);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (!texture->addr)
		return (false);
	return (true);
}

void	init_name_sprite(t_cub *cub, t_sprite *sprit, int j)
{
	int		i;
	char	filename[256];

	i = 1;
	while (i <= sprit->nframe)
	{
		snprintf(filename, sizeof(filename), "sprites/%d/%d.xpm", j, i);
		if (!init_texture(cub->mlx, filename, &cub->sprites_textures[j - 1][i
				- 1]))
		{
			free_cub(cub);
			quit_cub(MALLOC_ERROR);
			return ;
		}
		i++;
	}
}

void	init_texture_sprites(t_cub *cub)
{
	int	j;

	j = 0;
	while (j < 7)
	{
		init_name_sprite(cub, &cub->sprites[j], j + 1);
		j++;
	}
}

/**
 * @brief Pas besoin de comment car c'est du beau code mon gaté
 */
void	init_all_textures(t_cub *cub)
{
	if (!init_texture(cub->mlx, cub->map->pathn, &cub->texn))
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	if (!init_texture(cub->mlx, cub->map->paths, &cub->texs))
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	if (!init_texture(cub->mlx, cub->map->pathe, &cub->texe))
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	if (!init_texture(cub->mlx, cub->map->pathw, &cub->texw))
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	if (cub->map->ground
		&& !init_texture(cub->mlx, cub->map->ground, &cub->ground))
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	if (cub->map->sky && !init_texture(cub->mlx, cub->map->sky, &cub->sky))
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	if (!init_texture(cub->mlx, "textures/door.xpm", &cub->door))
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	init_texture_sprites(cub);
}
