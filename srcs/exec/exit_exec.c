/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 00:10:37 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/18 11:51:19 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	free_arg(t_args *args)
{
	int	i;

	i = 0;
	while (args->map[i])
		free(args->map[i++]);
	i = 0;
	while (args->doors[i])
		free(args->doors[i++]);
	if (args->doors)
		free(args->doors);
	free(args->map);
	free(args->pathe);
	free(args->pathn);
	free(args->paths);
	free(args->pathw);
	free(args->ground);
	free(args->sky);
}

void	quit_cub(int exit_code)
{
	if (exit_code == MALLOC_ERROR)
	{
		perror("Malloc Error");
		exit(EXIT_FAILURE);
	}
	else if (exit_code == SUCESS)
	{
		ft_printf("Program quit successfully !");
		exit(EXIT_SUCCESS);
	}
}

void	destroy_sprite(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < NSPRITE)
	{
		j = 0;
		while (j < cub->sprites[i].nframe)
		{
			if (cub->sprites_textures[i][j].img)
				mlx_destroy_image(cub->mlx, cub->sprites_textures[i][j].img);
			j++;
		}
		i++;
	}
}

void	free_cub(t_cub *cub)
{
	free_arg(cub->map);
	if (cub->img.img)
		mlx_destroy_image(cub->mlx, cub->img.img);
	if (cub->mmap.img)
		mlx_destroy_image(cub->mlx, cub->mmap.img);
	if (cub->texe.img)
		mlx_destroy_image(cub->mlx, cub->texn.img);
	if (cub->texs.img)
		mlx_destroy_image(cub->mlx, cub->texs.img);
	if (cub->texe.img)
		mlx_destroy_image(cub->mlx, cub->texe.img);
	if (cub->texw.img)
		mlx_destroy_image(cub->mlx, cub->texw.img);
	if (cub->ground.img)
		mlx_destroy_image(cub->mlx, cub->ground.img);
	if (cub->sky.img)
		mlx_destroy_image(cub->mlx, cub->sky.img);
	if (cub->door.img)
		mlx_destroy_image(cub->mlx, cub->door.img);
	mlx_destroy_window(cub->mlx, cub->win);
	destroy_sprite(cub);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
}
