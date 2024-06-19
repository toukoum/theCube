/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parsing_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:38:54 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/19 16:32:44 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	exit_parse_map(t_args *args, int exit_code, bool close_fd)
{
	if (close_fd)
		close(args->fd);
	free(args->pathe);
	free(args->pathn);
	free(args->paths);
	free(args->pathw);
	free(args->ground);
	free(args->sky);
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
