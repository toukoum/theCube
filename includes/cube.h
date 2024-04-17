/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:22:07 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/17 14:46:19 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __CUBE_H__
# define __CUBE_H__

# include "../libft-boost/ft_printf/includes/ft_printf.h"
# include "../libft-boost/gnl/includes/get_next_line_bonus.h"
# include "../libft-boost/libft_mandatory/includes/libft.h"

# include <mlx.h>

#include <X11/X.h>
#include <X11/keysym.h>


//event mlx
enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};


#endif