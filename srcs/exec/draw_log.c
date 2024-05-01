/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_log.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:16:41 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/01 20:06:29 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>


/**
 * @brief 
 * posX: 12.32px posY: 41.42px
 * dirX: 0.32px dirY: 0.67px
 * distleftRay: 34px
 * distcenterRay:42px
 * distrightRay: 24px
 * fov: 66deg
 * 
 * 
 * 
 * @param cub 
 */

void	draw_log_player(t_cub *cub)
{
	char result[100];
	char *tmp;

	ft_memcpy(result, "posX: ", 7);
	tmp = ft_itoa(cub->player.x);
	ft_strlcat(result, tmp, sizeof(result));
	free(tmp);
	ft_strlcat(result, "px, posY: ", sizeof(result));
	tmp = ft_itoa(cub->player.y);
	ft_strlcat(result, tmp, sizeof(result));
	free(tmp);
	mlx_string_put(cub->mlx, cub->win, WWIN - WMAP - 12, 35, CBLACK, result);
}
