/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:17:46 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/21 11:03:41 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void assign_path(char *line, char *cpy_line, t_args *args)
{
	char **target_path;
	
	if (cpy_line[0] == 'N' && cpy_line[1] == 'O')
		target_path = &args->pathN;
	else if (cpy_line[0] == 'S' && cpy_line[1] == 'O')
		target_path = &args->pathS;
	else if (cpy_line[0] == 'W' && cpy_line[1] == 'E')
		target_path = &args->pathO;
	else
		target_path = &args->pathE;
	
	if (*target_path)
		return (close(args->fd), quit(CLONE_ARGS));
	*target_path = ft_strdup(line);
}

void parse_texture_line(t_args *args, char *line, int i, char *cpy_line)
{
	int len_path;
	int fd_path;
	
	goto_next_char(&i, line);
	line = line + i;
	len_path = i;
	while (line[i] && !is_space(line[len_path]))
		len_path++;
	i = len_path;
	goto_next_char(&i, line);
	if (line[i])
		return (close(args->fd), quit(WRONG_ARG));
	line[len_path] = '\0';
	if (is_dir(line))
		return (close(args->fd), quit(FILE_DIR));
	if (!check_extension(line, ".xpm"))
		quit(EXTENSION_NAME);
	fd_path = open(line, O_RDONLY);
	if (fd_path == -1)
		return (close(args->fd), quit(WRONG_FILE));
	assign_path(line, cpy_line, args);
}

int	parse_line(char *line, t_args *args)
{
	int	i;
	char *cpy_line;

	cpy_line = line;
	i = 0;
	goto_next_char(&i, line);
	if (line[i] == 'F' || line[i] == 'C')
		parse_color_line(args, line, i + 1);
	else if (is_texture_id(line, i))
		parse_texture_line(args, line, i + 2, cpy_line);
	else if (!line[i])
		return (0);
	else if(!is_args_full(args))
		return (free(line), exit_parse_map(args, MISSING_ARG, true), 0);
	else
	{
		parse_map(args, line);
		return (1);
	}
	return (0);
}
