/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:17:58 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/21 11:05:50 by rgiraud          ###   ########.fr       */
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
	else if (exit_code == MISSING_MAP)
	{
		ft_printf("cub3D: Error: in map file, missing map");
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
	
	else if (exit_code == MPTY_LINE_MAP)
	{
		ft_printf("cub3D: Error: empty line in map");
		exit(EXIT_FAILURE);
	}

	else if (exit_code == INVALID_CHARACTER)
	{
		ft_printf("cub3D: Error: in map, invalid character");
		exit(EXIT_FAILURE);
	}
	else if (exit_code == MAP_NOT_LAST)
	{
		ft_printf("cub3D: Error: map is not the last element of file");
		exit(EXIT_FAILURE);
	}
	else if (exit_code == MISSING_ARG)
	{
		ft_printf("cub3D: Error: argument missing in .cub file");
		exit(EXIT_FAILURE);
	}
	else if (exit_code == MALLOC_ERROR)
	{
		ft_printf("cub3D: Error: malloc didn't work as expected");
		exit(EXIT_FAILURE);
	}

}

void	exit_parse_map(t_args *args, int exit_code, bool close_fd)
{
	if (close_fd)
		close(args->fd);
	if (args->pathE)
		free(args->pathE);
	if (args->pathN)
		free(args->pathN);
	if (args->pathS)
		free(args->pathS);
	if (args->pathO)
		free(args->pathO);
	quit(exit_code);
}

void exit_free_map(t_args *args, int i)
{
	while (i >= 0)
		free(args->map[i--]);
	free(args->map);
	exit_parse_map(args, MALLOC_ERROR, true);
}