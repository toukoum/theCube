/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:12:28 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/30 23:56:00 by rgiraud          ###   ########.fr       */
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

void	init_all_textures(t_cub *cub)
{
	if (!init_texture(cub->mlx, cub->map->pathN, &cub->texN))
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	if (!init_texture(cub->mlx, cub->map->pathS, &cub->texS))
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	if (!init_texture(cub->mlx, cub->map->pathE, &cub->texE))
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	if (!init_texture(cub->mlx, cub->map->pathW, &cub->texW))
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
}