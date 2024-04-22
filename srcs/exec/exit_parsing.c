/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:17:58 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/22 20:50:02 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	print_err_mess(char *log)
{
	ft_printf(RED "Error\n" RESET);
	ft_printf(REDL "> cub3D:" RESET);
	ft_printf(YELLOWB " %s\n\n\e[0m", log);
}

void	quit2(int exit_code)
{
	if (exit_code == MISSING_ARG)
		print_err_mess("argument missing in .cub file");
	else if (exit_code == MALLOC_ERROR)
		print_err_mess("malloc didn't work as expected");
	else if (exit_code == WALL_SURR)
		print_err_mess("map no surrounded with wall");
	else if (exit_code == ALL_GOOD)
	{
		ft_printf(GREENB "All arguments valid ✅\n\n" RESET);
		exit(EXIT_SUCCESS);
	}
	else if (exit_code == NO_PLAYER)
		print_err_mess("no player in the map");
	else if (exit_code == DUP_PLAYER)
		print_err_mess("duplicate player in map");
	exit(EXIT_SUCCESS);
}

void	quit(int exit_code)
{
	if (exit_code == NUMBERS_ARGC)
		print_err_mess("Usage: cub3D '/path/to/map.cub'");
	else if (exit_code == WRONG_FILE)
		print_err_mess("File: wrong file");
	else if (exit_code == EXTENSION_NAME)
		print_err_mess("File: not a .cub file");
	else if (exit_code == FILE_DIR)
		print_err_mess("file is a directory");
	else if (exit_code == MISSING_MAP)
		print_err_mess("in file, missing map");
	else if (exit_code == WRONG_ARG)
		print_err_mess("argument in file not valid");
	else if (exit_code == CLONE_ARGS)
		print_err_mess("dupplicate arg line");
	else if (exit_code == MPTY_LINE_MAP)
		print_err_mess("empty line in map");
	else if (exit_code == INVALID_CHARACTER)
		print_err_mess("in file, invalid character");
	else if (exit_code == MAP_NOT_LAST)
		print_err_mess("map is not the last element of file");
	else
		quit2(exit_code);
	exit(EXIT_FAILURE);
}
