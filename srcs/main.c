/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:21:25 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/17 15:29:53 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*mlx_win;
	t_data	img;
}				t_vars;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int close_prog(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
    // Ajoutez plus de gestion des touches ici
    return (0);
}

int handle_key(int keysym, t_vars *vars)
{
	ft_printf("handle key: %d\n", keysym);
    if (keysym == XK_Escape)  // Pour Linux
		close_prog(vars);
	
    // Ajoutez plus de gestion des touches ici
    return (0);
}

int	main(void)
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, img.img, 0, 0);
	vars.img = img;
	mlx_hook(vars.mlx_win, ON_DESTROY, StructureNotifyMask, close_prog, &vars);
	mlx_hook(vars.mlx_win, ON_KEYDOWN, KeyPressMask, handle_key, &vars);

	mlx_loop(vars.mlx);

}
