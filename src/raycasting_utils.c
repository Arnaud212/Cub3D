/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:15:41 by agiraud           #+#    #+#             */
/*   Updated: 2023/10/24 17:57:21 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_x(t_player *player, t_line *line, t_ray *ray)
{
	line->wall_inter = player->y + ray->r_dir_y
		* (ray->side_dist_x - ray->delta_dist_x);
	line->wall_inter -= (int)line->wall_inter;
	if (ray->r_dir_x < 0)
		line->wall_orientation = west;
	line->ray_length = ray->side_dist_x - ray->delta_dist_x;
}

void	get_y(t_player *player, t_line *line, t_ray *ray)
{
	line->wall_inter = player->x + ray->r_dir_x
		* (ray->side_dist_y - ray->delta_dist_y);
	line->wall_inter -= (int)line->wall_inter;
	if (ray->r_dir_y < 0)
		line->wall_orientation = north;
	line->ray_length = ray->side_dist_y - ray->delta_dist_y;
}

void	dda(t_map *map, t_line *line, t_ray *ray)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			line->wall_orientation = east;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			line->wall_orientation = south;
		}
		if (ray->map_x < 0 || ray->map_y < 0 || ray->map_x >= map->col
			|| ray->map_y >= map->lin)
		{
			line->ray_length = INFINITY;
			line->wall_inter = 0.0;
			break ;
		}
		if (map->map[ray->map_y * map->col + ray->map_x] == '1')
			break ;
	}
}

void	init_ray(t_player *player, int nb, t_ray *ray)
{
	ray->camera_x = (nb - (double) WIN_WIDTH / 2) / WIN_WIDTH * 2;
	ray->r_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->r_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	ray->delta_dist_x = fabs(1.0 / ray->r_dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->r_dir_y);
}

void	init_step(t_player *player, t_ray *ray)
{
	if (ray->r_dir_x < 0 && player->x > 0.0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if ((ray->r_dir_y < 0 && player->y > 0.0)
		|| (ray->r_dir_y > 0 && player->y < 0.0))
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}
