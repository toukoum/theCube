/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 00:10:37 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/30 15:03:06 by rgiraud          ###   ########.fr       */
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
}
void	quit_cub(int exit_code)
{
	if (exit_code == MALLOC_ERROR)
	{
		perror("Malloc Error !");
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
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_image(cub->mlx, cub->mmap.img);
	mlx_destroy_image(cub->mlx, cub->texN.img);
	mlx_destroy_image(cub->mlx, cub->texS.img);
	mlx_destroy_image(cub->mlx, cub->texE.img);
	mlx_destroy_image(cub->mlx, cub->texW.img);
	mlx_destroy_window(cub->mlx, cub->win);
	// mlx_destroy_display(cub->mlx);
	free(cub->mlx);
}
