/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parsing_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:38:54 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/26 09:07:54 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

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
	if (args->pathW)
		free(args->pathW);
	quit(exit_code);
}

/**
 * @brief if during allocation on row, 
 * a malloc doesn't work, we need to free 
 * all row previously malloced
 */
void	free_malloced_line_map(t_args *args, int i)
{
	while (i >= 0)
		free(args->map[i--]);
	free(args->map);
	exit_parse_map(args, MALLOC_ERROR, true);
}

void	free_all_map(t_args *args, int exit_code)
{
	int	i;

	i = 0;
	if (args->map)
	{
		while (args->map[i])
			if (args->map[i])	
				free(args->map[i++]);
		free(args->map);
	}
	i = 0;
	if (args->doors)
	{
		while (args->doors[i])
			if (args->doors[i])
				free(args->doors[i++]);
		free(args->doors);
	}
	exit_parse_map(args, exit_code, true);
}
