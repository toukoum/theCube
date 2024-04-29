/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:25:13 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/29 14:34:22 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

int	handle_key(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
		return (free_cub(cub), quit_cub(SUCESS), EXIT_FAILURE);
	else if (keycode == XK_w || keycode == XK_s || keycode == XK_a
		|| keycode == XK_d)
		move_player(keycode, cub, (t_int_coord){0, 0});
	else if (keycode == XK_Left || keycode == XK_Right)
		rotate_player(keycode, cub);
	render(cub);
	return (0);
}

int	handle_close_win(t_cub *cub)
{
	free_cub(cub);
	quit_cub(SUCESS);
	return (EXIT_SUCCESS);
}
