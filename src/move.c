/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:30:47 by agiraud           #+#    #+#             */
/*   Updated: 2023/10/30 17:55:14 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define SPEED_FRONT_BACK 0.1
#define SPEED_LEFT_RIGHT 0.05

void	mv_up(t_player *player, t_map *map)
{
	t_line	line;

	project_ray(player, map, WIN_WIDTH / 2, &line);
	if (line.ray_length <= SPEED_FRONT_BACK + 0.1)
		return ;
	player->x = player->x + (player->dir_x) * SPEED_FRONT_BACK;
	player->y = player->y + (player->dir_y) * SPEED_FRONT_BACK;
}

void	mv_down(t_player *player, t_map *map)
{
	t_line	line;

	player->dir_x = -player->dir_x;
	player->dir_y = -player->dir_y;
	project_ray(player, map, WIN_WIDTH / 2, &line);
	player->dir_x = -player->dir_x;
	player->dir_y = -player->dir_y;
	if (line.ray_length <= SPEED_FRONT_BACK + 0.1)
		return ;
	player->x = player->x - (player->dir_x) * SPEED_FRONT_BACK;
	player->y = player->y - (player->dir_y) * SPEED_FRONT_BACK;
}

void	mv_left(t_player *player, t_map *map)
{
	t_line	line;
	double	save;

	save = player->dir_x;
	player->dir_x = player->dir_y;
	player->dir_y = -save;
	project_ray(player, map, WIN_WIDTH / 2, &line);
	save = player->dir_x;
	player->dir_x = -player->dir_y;
	player->dir_y = save;
	if (line.ray_length <= SPEED_LEFT_RIGHT + 0.1)
		return ;
	player->x = player->x + (player->dir_y) * SPEED_LEFT_RIGHT;
	player->y = player->y - (player->dir_x) * SPEED_LEFT_RIGHT;
}

void	mv_right(t_player *player, t_map *map)
{
	t_line	line;
	double	save;

	save = player->dir_x;
	player->dir_x = -player->dir_y;
	player->dir_y = save;
	project_ray(player, map, WIN_WIDTH / 2, &line);
	save = player->dir_x;
	player->dir_x = player->dir_y;
	player->dir_y = -save;
	if (line.ray_length <= SPEED_LEFT_RIGHT + 0.1)
		return ;
	player->x = player->x - (player->dir_y) * SPEED_LEFT_RIGHT;
	player->y = player->y + (player->dir_x) * SPEED_LEFT_RIGHT;
}

void	turn_right(t_player *player)
{
	double	temp_x;

	temp_x = player->dir_x;
	player->dir_x = player->dir_x * COS_A - player->dir_y * SIN_A;
	player->dir_y = player->dir_y * COS_A + temp_x * SIN_A;
	player->plane_x = -player->dir_y * FOV;
	player->plane_y = player->dir_x * FOV;
}
