/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 00:10:37 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/14 13:55:27 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	free_arg(t_args *args)
{
	int	i;

	i = 0;
	while (args->map[i])
		free(args->map[i++]);
	free(args->map);
	free(args->pathE);
	free(args->pathN);
	free(args->pathS);
	free(args->pathW);
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

void	free_cub(t_cub *cub)
{
	free_arg(cub->map);
	if (cub->img.img)
		mlx_destroy_image(cub->mlx, cub->img.img);
	if (cub->mmap.img)
		mlx_destroy_image(cub->mlx, cub->mmap.img);
	if (cub->texE.img)
		mlx_destroy_image(cub->mlx, cub->texN.img);
	if (cub->texS.img)
		mlx_destroy_image(cub->mlx, cub->texS.img);
	if (cub->texE.img)
		mlx_destroy_image(cub->mlx, cub->texE.img);
	if (cub->texW.img)
		mlx_destroy_image(cub->mlx, cub->texW.img);
	if (cub->ground.img)
		mlx_destroy_image(cub->mlx, cub->ground.img);
	if (cub->sky.img)
		mlx_destroy_image(cub->mlx, cub->sky.img);
	mlx_destroy_window(cub->mlx, cub->win);
	//mlx_destroy_display(cub->mlx);
	free(cub->mlx);
}
