/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:15:34 by agiraud           #+#    #+#             */
/*   Updated: 2023/09/12 16:37:27 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	valid_map_line(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\n' || line[0] == '\0')
	{
		error_msg("empty line in map");
		return (0);
	}
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		if (!ft_is_in_charset(line[i], "01NSEW "))
		{
			error_msg("invalid character in map");
			return (0);
		}
		i++;
	}
	return (1);
}

char	*add_line_to_tmp_map(char *tmp_map, char *line)
{
	if (!valid_map_line(line))
	{
		free(tmp_map);
		free(line);
		return (NULL);
	}
	tmp_map = ft_strcat(tmp_map, line);
	if (!tmp_map)
	{
		error_msg("malloc error");
		return (NULL);
	}
	return (tmp_map);
}

char	*read_map(int fd, int *line_count)
{
	char	*tmp_map;
	char	*line;

	tmp_map = NULL;
	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		(*line_count)++;
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
	{
		error_msg("missing map");
		return (tmp_map);
	}
	while (line)
	{
		(*line_count)++;
		tmp_map = add_line_to_tmp_map(tmp_map, line);
		if (!tmp_map)
			return (NULL);
		line = get_next_line(fd);
	}
	return (tmp_map);
}

void	get_map_size(t_map *map, char *tmp_map)
{
	int	i;
	int	line_len;

	i = 0;
	line_len = 0;
	while (tmp_map[i])
	{
		if (tmp_map[i] == '\n')
		{
			if (line_len > map->col)
				map->col = line_len;
			line_len = 0;
			map->lin++;
		}
		else
			line_len++;
		i++;
	}
	if (tmp_map[i - 1] != '\n')
		map->lin++;
}

int	convert_tmp_map(t_map *map, char *tmp_map)
{
	int	c;
	int	l;
	int	index;

	l = -1;
	index = 0;
	map->map = malloc(map->col * map->lin * sizeof(char));
	if (!map->map)
		return (error_msg("malloc error"));
	while (++l < map->lin)
	{
		c = 0;
		while (tmp_map[index] && tmp_map[index] != '\n')
		{
			map->map[l * map->col + c] = tmp_map[index];
			index++;
			c++;
		}
		index++;
		c--;
		while (++c < map->col)
			map->map[l * map->col + c] = ' ';
	}
	return (0);
}
