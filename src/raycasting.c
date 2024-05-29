/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:09:30 by agiraud           #+#    #+#             */
/*   Updated: 2023/10/24 18:15:19 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	wall_type(t_ray *ray, t_line *line)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		line->wall_orientation = west;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		line->wall_orientation = south;
	}
}

void	project_ray(t_player *player, t_map *map, int nb, t_line *line)
{
	t_ray	ray;

	init_ray(player, nb, &ray);
	init_step(player, &ray);
	if (ray.map_x < 0 || ray.map_y < 0
		|| ray.map_x >= map->col || ray.map_y >= map->lin
		|| map->map[ray.map_y * map->col + ray.map_x] == '1')
		wall_type(&ray, line);
	else
		dda(map, line, &ray);
	if (ray.map_x < 0 || ray.map_y < 0
		|| ray.map_x > map->col || ray.map_y >= map->lin)
		return ;
	if (line->wall_orientation == east)
		get_x(player, line, &ray);
	else
		get_y(player, line, &ray);
}

int	frame(t_mlx *mlx, t_player *player, t_map *map)
{
	t_img	old_img;
	int		x;
	t_line	line;

	old_img = mlx->img;
	x = 0;
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->img.img_ptr)
		return (-1);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr,
			&mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	if (!mlx->img.addr)
		return (-1);
	while (x < WIN_WIDTH)
	{
		project_ray(player, map, x, &line);
		render_ray(mlx, map, x, &line);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	mlx_destroy_image(mlx->mlx_ptr, old_img.img_ptr);
	return (0);
}
