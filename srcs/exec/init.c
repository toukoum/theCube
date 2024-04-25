/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:02:42 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/24 19:18:24 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

int	handle_close_win(t_cub *cub)
{
	free_cub(cub);
	quit_cub(SUCESS);
	return (EXIT_SUCCESS);
}

int	handle_key(int keycode, t_cub *cub)
{
	ft_printf("keycode: %d\n", keycode);
	if (keycode == XK_Escape)
		return (free_cub(cub), quit_cub(SUCESS), EXIT_FAILURE);
	return (EXIT_FAILURE);
}

void	init_handle(t_cub *cub)
{
	mlx_hook(cub->win, ON_DESTROY, StructureNotifyMask, handle_close_win, cub);
	mlx_hook(cub->win, ON_KEYDOWN, KeyPressMask, handle_key, cub);
}

/**
 * @brief create mlx window and img
 *
 * @para
 * void render(t_cub *cub)
 *
 * m cub
 */
void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (quit_cub(MALLOC_ERROR));
	cub->win = mlx_new_window(cub->mlx, WWIN, HWIN, "The CUBE");
	if (!cub->win)
		return (free(cub->mlx), quit_cub(MALLOC_ERROR));
	cub->img.img = mlx_new_image(cub->mlx, WWIN, HWIN);
	if (!cub->img.img)
		return (mlx_destroy_window(cub->mlx, cub->win),
			mlx_destroy_display(cub->mlx), free(cub->mlx),
			quit_cub(MALLOC_ERROR));
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
	cub->mmap.img = mlx_new_image(cub->mlx, WMAP, HMAP);
	if (!cub->mmap.img)
		return (mlx_destroy_image(cub->mlx, cub->img.img),
			mlx_destroy_window(cub->mlx, cub->win),
			mlx_destroy_display(cub->mlx), free(cub->mlx),
			quit_cub(MALLOC_ERROR));
	cub->mmap.addr = mlx_get_data_addr(cub->mmap.img, &cub->mmap.bits_per_pixel,
			&cub->mmap.line_length, &cub->mmap.endian);
	init_handle(cub);
}
