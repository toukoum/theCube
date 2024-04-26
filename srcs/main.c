/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:21:25 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/26 00:09:52 by rgiraud          ###   ########.fr       */
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

void drawTile(t_cub * cub, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < TSIZE)
	{
		j = 0;
		while (j < TSIZE)
		{
			my_mlx_pixel_put(&cub->mmap, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

// int getTileColor(char **map, int mapPosX, int mapPosY)
// {
// 	if (!map[mapPosY] || !map[mapPosY][mapPosX] || is_space(map[mapPosY][mapPosX])) // dans la map mais a l'exterieur
// 		return (CWTF);
// 	if (map[mapPosY][mapPosX] == '1')
// 		return (CWALL);
// 	else if (map[mapPosY][mapPosX] == '0')
// 	{
// 		return (CGROUND);
// 	}
// 	else
// 		return (CLIME);
// }


// void	minimap(t_cub *cub)
// {
// 	int	tileX;
// 	int	tileY;
// 	double	playerX;
// 	double	playerY;
// 	double	mapPosX;
// 	double	mapPosY;
// 	int		y;
// 	int		x;

// 	tileX = WMAP / TSIZE;
// 	tileY = HMAP / TSIZE;
// 	playerX = cub->player.posX;
// 	playerY = cub->player.posY;
// 	// if (DEBUG)
// 	// {
// 	// 	ft_printf("> Size of minimap (x, y): %d %d\n", WMAP, HMAP);
// 	// 	ft_printf("> nombre de carreau (x, y): %d %d\n", tileX, tileY);
// 	// }
// 	printf("> pos of player (x, y): %f, %f\n", cub->player.posX, cub->player.posY);
	
// 	y = 0;
// 	while (y < tileY)
// 	{
// 		x = 0;
// 		while (x < tileX)
// 		{
// 			mapPosX = playerX - (tileX / 2) + x;
// 			mapPosY = playerY - (tileY / 2) + y;
// 			if ((y == tileY / 2) && (x == tileX / 2))
// 				drawTile(cub, x * TSIZE, y * TSIZE, CPLAYER);
// 			else if (mapPosX < 0 || mapPosX >= cub->map->width || mapPosY < 0
// 				|| mapPosY >= cub->map->height)
// 				drawTile(cub, x * TSIZE, y * TSIZE, CUNDEFINED);
// 			else
// 				drawTile(cub, x * TSIZE, y * TSIZE, getTileColor(cub->map->map, mapPosX, mapPosY));
// 			x++;
// 		}
// 		y++;
// 	}

// 	//draw border
// 	for (int i = 0; i < HMAP; i++)
// 	{
// 		for (int j = 0; j < WMAP; j++)
// 		{
// 			if (i == 0 || i == HMAP - 1)
// 				my_mlx_pixel_put(&cub->mmap, j, i, CWHITE);
// 			else if (j == 0 || j == WMAP - 1)
// 				my_mlx_pixel_put(&cub->mmap, j, i, CWHITE);
// 		}
// 	}
// 	mlx_put_image_to_window(cub->mlx, cub->win, cub->mmap.img, 20, 20);
// }


int getPixelColor(char **map, int x, int y)
{
	int mapPosX;	
	int mapPosY;	

	mapPosX = (int)(x / TSIZE);
	mapPosY = (int)(y / TSIZE);
	if (mapPosX > 0)
		mapPosX--;
	if (mapPosY > 0)
		mapPosY--;
	if (!map[mapPosY] || !map[mapPosY][mapPosX] || is_space(map[mapPosY][mapPosX])) // dans la map mais a l'exterieur
		return (CWTF);
	if (map[mapPosY][mapPosX] == '1')
		return (CWALL);
	else if (map[mapPosY][mapPosX] == '0')
	{
		return (CGROUND);
	}
	else
		return (CLIME);
}

void	minimap2(t_cub *cub)
{
	double	playerX;
	double	playerY;
	double	mapPosX;
	double	mapPosY;
	int		y;
	int		x;


	playerX = cub->player.posX * TSIZE;
	playerY = cub->player.posY * TSIZE;
	// if (DEBUG)
	// {
	// 	ft_printf("> Size of minimap (x, y): %d %d\n", WMAP, HMAP);
	// 	ft_printf("> nombre de carreau (x, y): %d %d\n", tileX, tileY);
	// }
	printf("> pos of player (x, y): %f, %f\n", cub->player.posX, cub->player.posY);
	
	y = 0;
	while (y < HMAP)
	{
		x = 0;
		while (x < WMAP) {
			mapPosX = playerX - (WMAP / 2) + x;  // Position in pixels
			mapPosY = playerY - (HMAP / 2) + y;
			int mapIndexX = mapPosX / TSIZE;  // Convert pixel position to map index
			int mapIndexY = mapPosY / TSIZE;

			if (mapIndexX < 0 || mapIndexX >= cub->map->width || mapIndexY < 0 || mapIndexY >= cub->map->height)
				my_mlx_pixel_put(&cub->mmap, x, y, CUNDEFINED);
			else
				my_mlx_pixel_put(&cub->mmap, x, y, getPixelColor(cub->map->map, x, y));
			x++;
    	}
		y++;
	}

	drawTile(cub, WMAP / 2, HMAP / 2, CPLAYER);

	//draw border
	for (int i = 0; i < HMAP; i++)
	{
		for (int j = 0; j < WMAP; j++)
		{
			if (i == 0 || i == HMAP - 1)
				my_mlx_pixel_put(&cub->mmap, j, i, CWHITE);
			else if (j == 0 || j == WMAP - 1)
				my_mlx_pixel_put(&cub->mmap, j, i, CWHITE);
		}
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->mmap.img, 20, 20);
}

void	render(t_cub *cub)
{
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			my_mlx_pixel_put(&cub->img, i, j, 0x00FF0000);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, WWIN / 2, HWIN
		/ 2);
	minimap2(cub);
}

void init_cub(t_cub *cub, t_args *args)
{
	cub->player.posX = args->pos_x;
	cub->player.posY = args->pos_y;
	cub->player.start_angle = args->start_angle;
	cub->map = args;
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
	init_mlx(&cub);
	init_cub(&cub, &args);
	render(&cub);
	mlx_loop(cub.mlx);
	return (EXIT_SUCCESS);
}
