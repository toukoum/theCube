/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:25:13 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/18 15:28:55 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void process_key_input(t_cub *cub)
{
	cub->rotSpeed = 0.1;
	if (cub->keyBuffer[XK_w])
		move_player(XK_w, cub);
    if (cub->keyBuffer[XK_s])
		move_player(XK_s, cub);
    if (cub->keyBuffer[XK_a])
		move_player(XK_a, cub);
    if (cub->keyBuffer[XK_d])
		move_player(XK_d, cub);
    if (cub->keyBuffer[XK_minus])
		change_fov(cub, XK_minus);
    if (cub->keyBuffer[XK_plus])
		change_fov(cub, XK_plus);
    if (cub->keyBuffer[XK_Left])
		rotate_player(XK_Left, cub);
    if (cub->keyBuffer[XK_Right])
		rotate_player(XK_Right, cub);
}

int	handle_key(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
		return (free_cub(cub), quit_cub(SUCESS), EXIT_FAILURE);
	cub->keyBuffer[keycode] = 1;
	return (0);
}

int handle_key_release(int keycode, t_cub *cub)
{
	cub->keyBuffer[keycode] = 0;

	return (0);
}

int	handle_close_win(t_cub *cub)
{
	free_cub(cub);
	quit_cub(SUCESS);
	return (EXIT_SUCCESS);
}


/**
 * @brief 
 * 
 * window 
 * 
 * -------------
 * 0px 400px  800px
 * 
 * -1   0	 1
 * 
 * 0         2
 * 
 * 0%        100%
 * 
 */


#define SENSITIVITY 0.0001
int handle_mouse(int x, int y, t_cub *cub)
{
    int deltaX = x - WWIN / 2;

    cub->rotSpeed = fabs(deltaX * SENSITIVITY);
	//printf("rotSpeed: %f, x: %d\n", cub->rotSpeed, x);
    if (x > (WWIN / 2)) {
		rotate_player(XK_Right, cub);
    }
	else
        rotate_player(XK_Left, cub);
	(void)y;
	mlx_mouse_move(cub->mlx, cub->win, WWIN / 2, HWIN / 2);

	return (0);
}