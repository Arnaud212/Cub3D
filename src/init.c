/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:20:06 by agiraud           #+#    #+#             */
/*   Updated: 2023/10/30 12:56:31 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_player(t_player *player)
{
	player->x = -1;
	player->y = -1;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->mv_forth = 0;
	player->mv_back = 0;
	player->mv_left = 0;
	player->mv_right = 0;
	player->turn_left = 0;
	player->turn_right = 0;
}

void	init_map(t_map *map)
{
	map->col = 0;
	map->lin = 0;
	map->map = NULL;
	map->floor = 0;
	map->ceiling = 0;
	map->n_text.name = NULL;
	map->s_text.name = NULL;
	map->e_text.name = NULL;
	map->w_text.name = NULL;
}
