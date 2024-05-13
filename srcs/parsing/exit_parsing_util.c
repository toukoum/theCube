/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parsing_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:38:54 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/30 14:27:22 by rgiraud          ###   ########.fr       */
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
void	exit_free_map(t_args *args, int i)
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
	while (args->map[i])
		free(args->map[i++]);
	free(args->map);
	exit_parse_map(args, exit_code, true);
}
