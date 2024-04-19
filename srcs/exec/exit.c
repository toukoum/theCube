/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:17:58 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/19 15:08:58 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <cube.h>

void quit(int exit_code){
	if (exit_code == NUMBERS_ARGC){
		ft_printf("cub3D: Error: Usage: ./cub3d <path/to/map.cub>");
		exit(EXIT_FAILURE);
	}
	else if (exit_code == WRONG_FILE)
	{
		ft_printf("cub3D: Error: File: wrong file");
		exit(EXIT_FAILURE);
	}

	else if (exit_code == EXTENSION_NAME)
	{
		ft_printf("cub3D: Error: File: not a .cub file");
		exit(EXIT_FAILURE);
	}

	else if (exit_code == FILE_DIR)
	{
		ft_printf("cub3D: Error: file is a directory");
		exit(EXIT_FAILURE);
	}
	else if (exit_code == MISSING_ARG)
	{
		ft_printf("cub3D: Error: in map file, missing arguments");
		exit(EXIT_FAILURE);
	}
	else if (exit_code == WRONG_ARG)
	{
		ft_printf("cub3D: Error: argument in file not valid");
		exit(EXIT_FAILURE);
	}
	else if (exit_code == CLONE_ARGS)
	{
		ft_printf("cub3D: Error: dupplicate arg line");
		exit(EXIT_FAILURE);
	}

}