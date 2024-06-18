/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:02:42 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/18 11:52:59 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

static void	init_start_angle(t_cub *cub)
{
	if (cub->player.start_angle == 'N')
	{
		cub->dir.y = -1;
		cub->plane.x = 0.66;
	}
	else if (cub->player.start_angle == 'S')
	{
		cub->dir.y = 1;
		cub->plane.x = -0.66;
	}
	else if (cub->player.start_angle == 'E')
	{
		cub->dir.x = 1;
		cub->plane.y = 0.66;
	}
	else if (cub->player.start_angle == 'W')
	{
		cub->dir.x = -1;
		cub->plane.y = -0.66;
	}
}

void	init_cub(t_cub *cub, t_args *args)
{
	cub->player.x = args->pos_x;
	cub->player.y = args->pos_y;
	cub->display_help = false;
	cub->player.start_angle = args->start_angle;
	cub->map = args;
	cub->dir.x = 0;
	cub->frame_sprite = 0;
	cub->can_move = true;
	cub->dir.y = 0;
	cub->plane.x = 0;
	cub->plane.y = 0;
	cub->frame_counter = 0;
	cub->rot_speed = 0.1;
	init_start_angle(cub);
	cub->doors = cub->map->doors;
}

/**
 * @brief init hook function
 */
void	init_handle(t_cub *cub)
{
	mlx_hook(cub->win, ON_DESTROY, StructureNotifyMask, handle_close_win, cub);
	mlx_hook(cub->win, ON_KEYDOWN, KeyPressMask, handle_key, cub);
	mlx_hook(cub->win, ON_KEYUP, KeyReleaseMask, handle_key_release, cub);
	mlx_hook(cub->win, ON_MOUSEMOVE, PointerMotionMask, handle_mouse, cub);
	mlx_hook(cub->win, ON_MOUSEDOWN, ButtonPressMask, handle_mouse_click, cub);
}

/**
 * @brief create mlx window and img
 * if any error, free all memory
 */
void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (free_arg(cub->map), quit_cub(MALLOC_ERROR));
	cub->win = mlx_new_window(cub->mlx, WWIN, HWIN, "The CUBE");
	if (!cub->win)
		return (free(cub->mlx), free_arg(cub->map), quit_cub(MALLOC_ERROR));
	cub->img.img = mlx_new_image(cub->mlx, WWIN, HWIN);
	if (!cub->img.img)
		return (mlx_destroy_window(cub->mlx, cub->win),
			mlx_destroy_display(cub->mlx), free(cub->mlx), free_arg(cub->map),
			quit_cub(MALLOC_ERROR));
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
	cub->mmap.img = mlx_new_image(cub->mlx, WMAP, HMAP);
	if (!cub->mmap.img)
		return (mlx_destroy_image(cub->mlx, cub->img.img),
			mlx_destroy_window(cub->mlx, cub->win),
			mlx_destroy_display(cub->mlx), free(cub->mlx), free_arg(cub->map),
			quit_cub(MALLOC_ERROR));
	cub->mmap.addr = mlx_get_data_addr(cub->mmap.img, &cub->mmap.bits_per_pixel,
			&cub->mmap.line_length, &cub->mmap.endian);
	init_handle(cub);
	init_all_textures(cub);
}
