/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:21:25 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/26 11:16:51 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void print_log_debug(t_args *args)
{
	int i;
	int j;

	i = 0;
	ft_printf("\n===== DEBUG MODE ====\n\n");
	ft_printf("> height/width of map: %d, %d\n", args->height, args->width);
	printf("> pos of player (x, y): %f, %f\n", args->pos_x, args->pos_y);
	ft_printf("> map color floor (r, g, b): %u, %u, %u\n", args->floorColor.r,
		args->floorColor.g, args->floorColor.b);
	ft_printf("> map color ceiling (r, g, b): %u, %u, %u\n",
		args->ceilColor.r, args->ceilColor.g, args->ceilColor.b);
	ft_printf("> map: \n\n");
	while (i < args->height)
	{
		j = 0;
		while (args->map[i][j])
		{
			if (is_space(args->map[i][j]))
				ft_printf(".");
			else
				ft_printf("%c", args->map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("\n");
}

void	render(t_cub *cub)
{
	printf("> pos of player (x, y): %f, %f\n", cub->player.posX, cub->player.posY);
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			my_mlx_pixel_put(&cub->img, i, j, 0x00FF0000);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, WWIN / 2, HWIN
		/ 2);
	minimap(cub, cub->player.posX * TSIZE, cub->player.posY * TSIZE);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_cub	cub;

	ft_bzero(&cub, sizeof(t_cub));
	if (argc != 2)
		quit(NUMBERS_ARGC);
	parse(&args, argv[1]);
	if (DEBUG)
		print_log_debug(&args);
	init_cub(&cub, &args);
	init_mlx(&cub);
	render(&cub);
	mlx_loop(cub.mlx);
	return (EXIT_SUCCESS);
}
