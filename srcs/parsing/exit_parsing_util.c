/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parsing_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:38:54 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/22 12:41:25 by rgiraud          ###   ########.fr       */
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
	if (args->pathO)
		free(args->pathO);
	quit(exit_code);
}

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
