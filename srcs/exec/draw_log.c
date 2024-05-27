/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_log.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:16:41 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/26 12:03:29 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	draw_len_ray(t_cub *cub, double distRay, char *name, int line_top)
{
	char	result[100];
	char	*tmp;

	ft_memcpy(result, name, 16);
	if (distRay < 0.1 && distRay > -0.1)
		tmp = get_value_float(0);
	else
		tmp = get_value_float(distRay);
	if (!tmp)
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	ft_strlcat(result, tmp, sizeof(result));
	free(tmp);
	mlx_string_put(cub->mlx, cub->win, WWIN - WMAP - 12, line_top, CWHITE,
		result);
}

void	draw_dir(t_cub *cub)
{
	char	result[100];
	char	*tmp;

	ft_memcpy(result, "dirX: ", 7);
	if (cub->dir.x < 0.1 && cub->dir.x > -0.1)
		tmp = get_value_float(0);
	else
		tmp = get_value_float(cub->dir.x);
	if (!tmp)
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	ft_strlcat(result, tmp, sizeof(result));
	free(tmp);
	ft_strlcat(result, " dirY: ", sizeof(result));
	if (cub->dir.y < 0.1 && cub->dir.y > -0.1)
		tmp = get_value_float(0);
	else
		tmp = get_value_float(cub->dir.y);
	if (!tmp)
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	ft_strlcat(result, tmp, sizeof(result));
	free(tmp);
	mlx_string_put(cub->mlx, cub->win, WWIN - WMAP - 12, 50, CWHITE, result);
}

void	draw_pos(t_cub *cub)
{
	char	result[100];
	char	*tmp;

	ft_memcpy(result, "posX: ", 7);
	if (cub->player.x < 0.1 && cub->player.x > -0.1)
		tmp = get_value_float(cub->player.x * 0.1);
	else
		tmp = get_value_float(cub->player.x);
	if (!tmp)
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	ft_strlcat(result, tmp, sizeof(result));
	free(tmp);
	ft_strlcat(result, " posY: ", sizeof(result));
	if (cub->player.y < 0.1 && cub->player.y > -0.1)
		tmp = get_value_float(0);
	else
		tmp = get_value_float(cub->player.y);
	if (!tmp)
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	ft_strlcat(result, tmp, sizeof(result));
	free(tmp);
	mlx_string_put(cub->mlx, cub->win, WWIN - WMAP - 12, 35, CWHITE, result);
}

/**
 * @brief
 * posX: 12.32px posY: 41.42px
 * dirX: 0.32px dirY: 0.67px
 * distleftRay: 34px
 * distcenterRay:42px
 * distrightRay: 24px
 * fov: 66deg
 * @param cub
 */
void	draw_log_player(t_cub *cub)
{
	draw_pos(cub);
	draw_dir(cub);
	draw_len_ray(cub, cub->wallDist[0], "distLeftRay:   ", 95);
	draw_len_ray(cub, cub->wallDist[WWIN / 2], "distCenterRay: ", 80);
	draw_len_ray(cub, cub->wallDist[WWIN - 1], "distRightRay:  ", 65);
	draw_fov(cub);
}
