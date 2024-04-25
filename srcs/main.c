/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:21:25 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/25 12:17:25 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	minimap(t_cub *cub)
{
	size_t tileX;
	size_t tileY;

	tileX = WMAP / TSIZE;
	tileY = HMAP / TSIZE;
	
	if (DEBUG)
	{
		ft_printf("> Size of minimap (x, y): %d %d\n", WMAP, HMAP);
		ft_printf("> nombre de carreau (x, y): %d %d\n", tileX, tileY);
		
	}
	size_t to_draw;
	to_draw = 0;
	if (cub->arg->pos_y < (tileY / 2))
	{
		to_draw = tileY / 2 - cub->arg->pos_y;
	}
	ft_printf("to_draw: %d\n", to_draw);
	for (size_t i = 0; i < to_draw; i++)
	{
		for (size_t j = 0; j < WMAP; j++)
		{
			my_mlx_pixel_put(&cub->mmap, i, j, 0x00FF00);  // Blanc		
		}
	}
	
	for (int i = 0; i < WMAP; i++)
    {
		my_mlx_pixel_put(&cub->mmap, i, HMAP / 2, 0xFFFFFF);  // Blanc

        // for (int j = 0; j < HMAP; j++)
        // {
        //     // Calcul pour alternance de couleurs dans le damier
        //     int x_cell = i / TSIZE;  // Index de la cellule actuelle en x
        //     int y_cell = j / TSIZE;  // Index de la cellule actuelle en y

        //     // Alternance de couleurs entre les cellules
        //     if ((x_cell + y_cell) % 2 == 0)
        //         my_mlx_pixel_put(&cub->mmap, i, j, 0x0000FF);  // Bleu
        //     else
        //         my_mlx_pixel_put(&cub->mmap, i, j, 0xFFFFFF);  // Blanc
        // }
    }
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mmap.img, 20, 20);
}

void	render(t_cub *cub)
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			my_mlx_pixel_put(&cub->img, i, j, 0x00FF0000);
		}
	}	
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, WWIN / 2, HWIN
		/ 2);
	minimap(cub);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_cub	cub;

	ft_bzero(&cub, sizeof(t_cub));
	if (argc != 2)
		quit(NUMBERS_ARGC);
	parse(&args, argv[1]);
	cub.arg = &args;
	init_mlx(&cub);
	render(&cub);
	mlx_loop(cub.mlx);
	return (EXIT_SUCCESS);
}
