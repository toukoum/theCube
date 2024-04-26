/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:02:42 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/26 11:19:20 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

int	handle_close_win(t_cub *cub)
{
	free_cub(cub);
	quit_cub(SUCESS);
	return (EXIT_SUCCESS);
}

/**
 * @brief a finir
 */
void move_player(int keycode, t_cub *cub, int mapIndexX, int mapIndexY)
{
    double nextX;
    double nextY;

	nextX = cub->player.posX;
	nextY = cub->player.posY;
    if (keycode == XK_w)
        nextY -= MOVESPEED;
    else if (keycode == XK_s)
        nextY += 1;
    else if (keycode == XK_a)
        nextX -= MOVESPEED;
    else if (keycode == XK_d)
        nextX += 1;
    mapIndexX = (int)(nextX);
    mapIndexY = (int)(nextY);
    if (cub->map->map[mapIndexY][mapIndexX] == '0' || cub->map->map[mapIndexY][mapIndexX] == cub->player.start_angle) {
		if (keycode == XK_d)
			nextX -= 0.9;
		if (keycode == XK_s)
			nextY -= 0.9;
        cub->player.posX = nextX;
        cub->player.posY = nextY;
    } 
	else
        printf("Movement blocked at (%d, %d) %f, %f\n", mapIndexX, mapIndexY, nextX, nextY);
}

void init_cub(t_cub *cub, t_args *args)
{
	cub->player.posX = args->pos_x;
	cub->player.posY = args->pos_y;
	cub->player.start_angle = args->start_angle;
	cub->map = args;
}

int	handle_key(int keycode, t_cub *cub)
{
	ft_printf("keycode: %d\n", keycode);
	if (keycode == XK_Escape)
		return (free_cub(cub), quit_cub(SUCESS), EXIT_FAILURE);
	else if (keycode == XK_w || keycode == XK_s || keycode == XK_a
		|| keycode == XK_d)
		move_player(keycode, cub, 0, 0);
	render(cub);
	return (0);
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
