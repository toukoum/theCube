/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:17:46 by rgiraud           #+#    #+#             */
/*   Updated: 2024/06/18 11:13:53 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	assign_path(char *line, char *cpy_line, t_args *args)
{
	char	**target_path;

	if (!ft_strncmp("NO", cpy_line, 2))
		target_path = &args->pathN;
	else if (!ft_strncmp("SO", cpy_line, 2))
		target_path = &args->pathS;
	else if (!ft_strncmp("WE", cpy_line, 2))
		target_path = &args->pathW;
	else if (!ft_strncmp("SK", cpy_line, 2))
		target_path = &args->sky;
	else if (!ft_strncmp("GR", cpy_line, 2))
		target_path = &args->ground;
	else
		target_path = &args->pathE;
	if (*target_path)
		return (free(cpy_line), exit_parse_map(args, CLONE_ARGS, true));
	*target_path = ft_strdup(line);
}

void	parse_texture_line(t_args *args, char *line, int i, char *cpy_line)
{
	int	len_path;
	int	fd_path;

	goto_next_char(&i, line);
	line = line + i;
	len_path = i;
	while (line[i] && !is_space(line[len_path]))
		len_path++;
	i = len_path;
	goto_next_char(&i, line);
	if (line[i])
		return (free(cpy_line), exit_parse_map(args, WRONG_ARG, true));
	line[len_path] = '\0';
	if (is_dir(line))
		return (free(cpy_line), exit_parse_map(args, FILE_DIR, true));
	if (!check_extension(line, ".xpm"))
		return (free(cpy_line), exit_parse_map(args, EXTENSION_NAME, true));
	fd_path = open(line, O_RDONLY);
	if (fd_path == -1)
		return (free(cpy_line), exit_parse_map(args, WRONG_FILE, true));
	close(fd_path);
	assign_path(line, cpy_line, args);
}

bool	to_many_floor(t_args *args)
{
	if (args->floorColor.is_correct && args->ceilColor.is_correct
		&& (args->ground || args->sky))
		return (true);
	if (args->ground && args->sky && (args->floorColor.is_correct
			|| args->ceilColor.is_correct))
		return (true);
	else if (args->ground && args->sky && !(args->floorColor.is_correct
			|| args->ceilColor.is_correct))
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
	char	*cpy_line;

	cpy_line = line;
	i = 0;
	goto_next_char(&i, line);
	if (line[i] == 'F' || line[i] == 'C')
		parse_color_line(args, line, i + 1);
	else if (is_texture_id(line, i))
		parse_texture_line(args, line, i + 2, cpy_line);
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
