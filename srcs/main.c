/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:21:25 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/18 11:43:17 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	print_log_debug(t_args *args)
{
	int	i;
	int	j;

	i = -1;
	ft_printf("\n===== DEBUG MODE ====\n\n");
	ft_printf("> height/width of map: %d, %d\n", args->height, args->width);
	printf("> pos of player (x, y): %f, %f\n", args->pos_x, args->pos_y);
	ft_printf("> map color floor (r, g, b): %u, %u, %u\n", args->floor_col.r,
		args->floor_col.g, args->floor_col.b);
	ft_printf("> map color ceiling (r, g, b): %u, %u, %u\n", args->ceil_col.r,
		args->ceil_col.g, args->ceil_col.b);
	ft_printf("> map: \n\n");
	while (++i < args->height)
	{
		j = -1;
		while (args->map[i][++j])
		{
			if (is_space(args->map[i][j]))
				ft_printf(".");
			else
				ft_printf("%c", args->map[i][j]);
		}
		ft_printf("\n");
	}
	ft_printf("\n");
}

int	render(t_cub *cub)
{
	cub->frame_counter++;
	if (cub->frame_counter % 7 == 0)
		cub->frame_sprite++;
	draw_all(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mmap.img, 20, 20);
	if (cub->display_help)
		draw_log_player(cub);
	else
		mlx_string_put(cub->mlx, cub->win, WWIN - WMAP + 50, 35, CUNDEFINED,
			"h for informations");
	process_key_input(cub);
	return (ALL_GOOD);
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
	init_pos_sprite(&cub);
	init_mlx(&cub);
	mlx_loop_hook(cub.mlx, &render, &cub);
	mlx_loop(cub.mlx);
	return (EXIT_SUCCESS);
}
