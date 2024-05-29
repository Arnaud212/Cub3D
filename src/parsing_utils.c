/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:40:34 by agiraud           #+#    #+#             */
/*   Updated: 2023/09/19 18:26:37 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_filename(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len < 5)
		return (1);
	if (ft_strcmp(&name[len - 4], ".cub"))
		return (1);
	if (name[len - 5] == '/')
		return (1);
	return (0);
}

int	id_is_texture(char *line)
{
	return (!ft_strncmp(line, "NO", 2)
		|| !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "EA", 2)
		|| !ft_strncmp(line, "WE", 2));
}

int	id_is_color(char *line)
{
	return (line[0] == 'F' || line[0] == 'C');
}

int	get_tex_file(t_map *map, char *line, char *tex_file)
{
	if (!ft_strncmp(line, "NO", 2))
	{
		if (map->n_text.name)
			return (1);
		map->n_text.name = tex_file;
	}
	if (!ft_strncmp(line, "SO", 2))
	{
		if (map->s_text.name)
			return (1);
		map->s_text.name = tex_file;
	}
	if (!ft_strncmp(line, "EA", 2))
	{
		if (map->e_text.name)
			return (1);
		map->e_text.name = tex_file;
	}
	if (!ft_strncmp(line, "WE", 2))
	{
		if (map->w_text.name)
			return (1);
		map->w_text.name = tex_file;
	}
	return (0);
}

int	touches_zero(t_map *map, int x, int y)
{
	if (x > 0 && map->map[y * map->col + x - 1] == '0')
		return (1);
	if (x < map->col - 1 && map->map[y * map->col + x + 1] == '0')
		return (1);
	if (y > 0 && map->map[(y - 1) * map->col + x] == '0')
		return (1);
	if (y < map->lin - 1 && map->map[(y + 1) * map->col + x] == '0')
		return (1);
	return (0);
}
