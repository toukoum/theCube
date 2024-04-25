/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:21:25 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/25 16:43:14 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>


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

int getTileColor(char **map, int mapPosX, int mapPosY)
{
	if (!map[mapPosY] || !map[mapPosY][mapPosX] || is_space(map[mapPosY][mapPosX])) // dans la map mais a l'exterieur
		return (CWTF);
	if (map[mapPosY][mapPosX] == '1')
		return (CWALL);
	else if (map[mapPosY][mapPosX] == '0')
	{
		return (CGROUND);
	}
	else
		return (CPLAYER);
}


void	minimap(t_cub *cub)
{
	int	tileX;
	int	tileY;
	int	playerX;
	int	playerY;
	int	mapPosX;
	int	mapPosY;
	int		y;
	int		x;

	tileX = WMAP / TSIZE;
	tileY = HMAP / TSIZE;
	playerX = cub->arg->pos_x;
	playerY = cub->arg->pos_y;
	if (DEBUG)
	{
		ft_printf("> Size of minimap (x, y): %d %d\n", WMAP, HMAP);
		ft_printf("> nombre de carreau (x, y): %d %d\n", tileX, tileY);
	}
	y = 0;
	while (y < tileY)
	{
		x = 0;
		while (x < tileX)
		{
			ft_printf("draw tile !\n");
			mapPosX = playerX - (tileX / 2) + x;
			mapPosY = playerY - (tileY / 2) + y;
			if (mapPosX < 0 || mapPosX >= cub->arg->width || mapPosY < 0
				|| mapPosY >= cub->arg->height)
				drawTile(cub, x * TSIZE, y * TSIZE, CUNDEFINED);
			else
				drawTile(cub, x * TSIZE, y * TSIZE, getTileColor(cub->arg->map, mapPosX, mapPosY));
			x++;
		}
		y++;
	}

	//draw border
	for (int i = 0; i < HMAP; i++)
	{
		for (int j = 0; j < WMAP; j++)
		{
			if (i == 0 || i == HMAP - 1)
				my_mlx_pixel_put(&cub->mmap, j, i, MWHITE);
			else if (j == 0 || j == WMAP - 1)
				my_mlx_pixel_put(&cub->mmap, j, i, MWHITE);
		}
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
