/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:25:13 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/19 13:16:50 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	process_key_input(t_cub *cub)
{
	cub->rot_speed = 0.02;
	if (cub->keybuffer[XK_w])
		move_player(XK_w, cub);
	if (cub->keybuffer[XK_s])
		move_player(XK_s, cub);
	if (cub->keybuffer[XK_a])
		move_player(XK_a, cub);
	if (cub->keybuffer[XK_d])
		move_player(XK_d, cub);
	if (cub->keybuffer[XK_Left])
		rotate_player(XK_Left, cub);
	if (cub->keybuffer[XK_Right])
		rotate_player(XK_Right, cub);
}

int	handle_key(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
		return (free_cub(cub), quit_cub(SUCESS), EXIT_FAILURE);
	if (keycode == XK_space)
	{
		open_door(cub);
		play_animation(cub);
	}
	if (keycode == XK_minus)
		change_fov(cub, XK_minus);
	if (keycode == XK_plus)
		change_fov(cub, XK_plus);
	if (keycode == XK_h)
		cub->display_help = !cub->display_help;
	cub->keybuffer[keycode] = 1;
	return (0);
}

int	handle_key_release(int keycode, t_cub *cub)
{
	cub->keybuffer[keycode] = 0;
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
 * -1   0		1
 *
 * 0         2
 *
 * 0%        100%
 *
 */

int	handle_mouse(int x, int y, t_cub *cub)
{
	int	delta_x;

	delta_x = x - WWIN / 2;
	cub->rot_speed = fabs(delta_x * delta_x * SENSITIVITY);
	if (x > (WWIN / 2))
	{
		rotate_player(XK_Right, cub);
	}
	else
		rotate_player(XK_Left, cub);
	(void)y;
	return (0);
}
