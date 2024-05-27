/* ***************************************x*********************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:12:21 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/26 11:03:48 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

int	handle_mouse_click(int keycode, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (keycode == 1)
	{
		change_fov(cub, XK_plus);
	}
	else if (keycode == 2)
	{
		change_fov(cub, XK_minus);
	}
	return (ALL_GOOD);
}