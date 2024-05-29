/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:47:30 by agiraud           #+#    #+#             */
/*   Updated: 2023/09/12 16:36:44 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	parse_line_tex(t_map *map, char *line)
{
	int		i;
	char	*tex_file;

	i = 2;
	if (!ft_is_whitespace(line[2]))
		return (error_msg("invalid texture identifier"));
	while (ft_is_whitespace(line[i]) && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		return (error_msg("invalid texture identifier"));
	tex_file = ft_strdup(&line[i]);
	if (!tex_file)
		return (error_msg("malloc error"));
	tex_file[ft_strlen(tex_file) - 1] = '\0';
	if (get_tex_file(map, line, tex_file))
	{
		free(tex_file);
		return (error_msg("double texture identifier"));
	}
	return (0);
}

int	read_colors(char *line, unsigned int *color)
{
	int	i;

	i = 2;
	if (ft_atoi(&line[i]) < 0 || ft_atoi(&line[i]) > 255)
		return (1);
	*color = (unsigned) ft_atoi(&line[1]) << 16;
	while (line[i] != ',' && line[i])
		i++;
	if (line[i] != ',')
		return (1);
	i++;
	if (ft_atoi(&line[i]) < 0 || ft_atoi(&line[i]) > 255)
		return (1);
	*color += (unsigned) ft_atoi(&line[i]) << 8;
	while (line[i] != ',' && line[i])
		i++;
	if (line[i] != ',')
		return (1);
	i++;
	if (ft_atoi(&line[i]) < 0 || ft_atoi(&line[i]) > 255)
		return (1);
	*color += (unsigned) ft_atoi(&line[i]);
	return (0);
}

int	parse_line_color(t_map *map, char *line)
{
	unsigned int	color;

	if (!ft_is_whitespace(line[1]))
		return (error_msg("invalid color identifier"));
	if (read_colors(line, &color))
		return (error_msg("invalid or missing RGB value"));
	if ((line[0] == 'C' && map->ceiling) || (line [0] == 'F' && map->floor))
		return (error_msg("double color identifier"));
	if (line[0] == 'C')
		map->ceiling = color;
	else
		map->floor = color;
	return (0);
}

int	parse_line_id(t_map *map, char *line)
{
	if (id_is_texture(line))
		return (parse_line_tex(map, line));
	if (id_is_color(line))
		return (parse_line_color(map, line));
	return (error_msg("invalid identifier"));
}

int	parse_file_id(int fd, t_map *map, int *line_count)
{
	char	*line;
	int		nb_id;

	nb_id = 0;
	line = get_next_line(fd);
	while (line)
	{
		(*line_count)++;
		if (line[0] != '\n')
		{
			if (parse_line_id(map, line))
			{
				free(line);
				return (1);
			}
			nb_id++;
		}
		free(line);
		if (nb_id == 6)
			return (0);
		line = get_next_line(fd);
	}
	return (error_msg("missing identifier"));
}
