/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:17:46 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/24 15:10:53 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	assign_path(char **split, char *line, t_args *args)
{
	char	**target_path;

	if (!ft_strncmp("NO", split[0], 2))
		target_path = &args->paths;
	else if (!ft_strncmp("SO", split[0], 2))
		target_path = &args->pathn;
	else if (!ft_strncmp("WE", split[0], 2))
		target_path = &args->pathw;
	else if (!ft_strncmp("SK", split[0], 2))
		target_path = &args->sky;
	else if (!ft_strncmp("GR", split[0], 2))
		target_path = &args->ground;
	else
		target_path = &args->pathe;
	if (*target_path)
		return (free(line), free_multisplit(split), handle_error(args, NULL));
	*target_path = ft_strdup(split[1]);
	if (!*target_path)
	{
		free_multisplit(split);
		handle_error(args, NULL);
	}
}

void	parse_texture_line(t_args *args, char *line)
{
	char	**split;
	int		fd_path;

	split = multisplit(line, " \t\n");
	if (split_size(split) != 2 || !split)
		return (free_multisplit(split), handle_error(args, line));
	if (is_dir(split[1]))
		return (free_multisplit(split), handle_error(args, line));
	if (!check_extension(split[1], ".xpm"))
		return (free_multisplit(split), handle_error(args, line));
	fd_path = open(split[1], O_RDONLY);
	if (fd_path == -1)
		return (free_multisplit(split), handle_error(args, line));
	return (close(fd_path), assign_path(split, line, args),
		free_multisplit(split));
}

bool	to_many_floor(t_args *args)
{
	if (args->floor_col.is_correct && args->ceil_col.is_correct && (args->ground
			|| args->sky))
		return (true);
	if (args->ground && args->sky && (args->floor_col.is_correct
			|| args->ceil_col.is_correct))
		return (true);
	else if (args->ground && args->sky && !(args->floor_col.is_correct
			|| args->ceil_col.is_correct))
		args->is_floor_texture = true;
	return (false);
}

/**
 * @brief determine if the line is:
 * 	- color line
 *  - texture path line
 * 	- the start of the map
 *
 * @param line
 * @param args
 * @return int
 */
int	parse_line(char *line, t_args *args)
{
	int		i;

	i = 0;
	goto_next_char(&i, line);
	if (line[i] == 'F' || line[i] == 'C')
		parse_color_line(args, line, i + 1);
	else if (is_texture_id(line, i))
		parse_texture_line(args, line);
	else if (!line[i])
		return (ALL_PAS_GOOD);
	else if ((!is_args_full(args) && (!is_texture_id(line, i)
				&& !(line[i] == 'F' || line[i] == 'C'))) || to_many_floor(args))
		return (free(line), exit_parse_map(args, INVALID_CHARACTER, true), 0);
	else if (!is_args_full(args))
		return (free(line), exit_parse_map(args, MISSING_ARG, true), 0);
	else
	{
		parse_map(args, line);
		return (ALL_GOOD);
	}
	return (ALL_PAS_GOOD);
}
