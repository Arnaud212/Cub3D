/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:22:04 by agiraud           #+#    #+#             */
/*   Updated: 2023/10/13 19:13:03 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	player_start(t_player *player, int x, int y, char dir)
{
	if (dir == 'N')
		player->dir_y = -1.0;
	if (dir == 'S')
		player->dir_y = 1.0;
	if (dir == 'E')
		player->dir_x = 1.0;
	if (dir == 'W')
		player->dir_x = -1.0;
	player->x = x + 0.5;
	player->y = y + 0.5;
	player->plane_x = -player->dir_y * FOV;
	player->plane_y = player->dir_x * FOV;
}

int	find_player(t_player *player, t_map *map)
{
	int	x;
	int	y;
	int	player_found;

	y = 0;
	player_found = 0;
	while (y < map->lin)
	{
		x = 0;
		while (x < map->col)
		{
			if (ft_is_in_charset(map->map[y * map->col + x], "NSEW"))
			{
				if (player_found)
					return (1);
				player_found = 1;
				player_start(player, x, y, map->map[y * map->col + x]);
				map->map[y * map->col + x] = '0';
			}
			x++;
		}
		y++;
	}
	return (!player_found);
}

int	parse_file_map(int fd, t_map *map, int *line_count)
{
	char	*tmp_map;

	tmp_map = read_map(fd, line_count);
	if (!tmp_map)
		return (1);
	get_map_size(map, tmp_map);
	if (convert_tmp_map(map, tmp_map))
	{
		free(tmp_map);
		return (1);
	}
	free(tmp_map);
	return (0);
}

int	valid_map(t_map *map)
{
	int	c;
	int	l;

	l = 0;
	while (l < map->lin)
	{
		c = 0;
		while (c < map->col)
		{
			if ((c == 0 || c == map->col - 1 || l == 0 || l == map->lin - 1)
				&& map->map[l * map->col + c] == '0')
			{
				error_msg("map not surrounded by walls");
				return (0);
			}
			if (map->map[l * map->col + c] == ' ' && touches_zero(map, c, l))
			{
				error_msg("map not surrounded by walls");
				return (0);
			}
			c++;
		}
		l++;
	}
	return (1);
}

int	parse(int argc, char **argv, t_map *map, t_player *player)
{
	int	fd;
	int	line_count;

	if (argc != 2)
		return (error_msg("wrong number of arguments"));
	if (check_filename(argv[1]))
		return (error_msg("wrong file extension"));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (error_msg("can't open file"));
	line_count = 0;
	if (parse_file_id(fd, map, &line_count)
		|| parse_file_map(fd, map, &line_count))
	{
		close(fd);
		return (1);
	}
	close(fd);
	if (find_player(player, map))
		return (error_msg("wrong number of players"));
	return (!valid_map(map));
}
