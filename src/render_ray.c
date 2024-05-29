/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:26:19 by agiraud           #+#    #+#             */
/*   Updated: 2023/10/24 18:02:17 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel(t_img *img, int nb, int x, unsigned int color)
{
	char	*pixel;

	pixel = img->addr + (x * img->line_length + nb * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void	pixel_ceiling_floor(t_mlx *mlx, t_map *map, int nb, t_line *line)
{
	int	size;
	int	x;

	x = 0;
	size = (int)(WIN_HEIGHT / line->ray_length);
	if (line->ray_length < 0.001)
		size = 50000;
	while (x < WIN_HEIGHT / 2 - size / 2 && x < WIN_HEIGHT / 2)
	{
		put_pixel(&mlx->img, nb, x, map->ceiling);
		x++;
	}
	x = WIN_HEIGHT;
	while (x >= WIN_HEIGHT / 2 + size / 2 && x >= WIN_HEIGHT / 2)
	{
		put_pixel(&mlx->img, nb, x, map->floor);
		x--;
	}
}

t_text	*wall_text(t_map *map, t_line *line)
{
	if (line->wall_orientation == north)
		return (&map->n_text);
	if (line->wall_orientation == south)
		return (&map->s_text);
	if (line->wall_orientation == east)
		return (&map->e_text);
	return (&map->w_text);
}

void	render_ray(t_mlx *mlx, t_map *map, int nb, t_line *line)
{
	int				size_wall;
	int				x;
	t_text			*text;
	unsigned int	color;
	char			*str;

	size_wall = (int)(WIN_HEIGHT / line->ray_length);
	if (line->ray_length < 0.001)
		size_wall = 50000;
	pixel_ceiling_floor(mlx, map, nb, line);
	x = WIN_HEIGHT / 2 - size_wall / 2;
	if (x < 0)
		x = 0;
	text = wall_text(map, line);
	while (x < size_wall / 2 + WIN_HEIGHT / 2 && x < WIN_HEIGHT)
	{
		str = text->img.addr + ((int)(text->height
					* (x - WIN_HEIGHT / 2 + size_wall / 2) / size_wall)
				* text->img.line_length
				+ (int)(text->width * line->wall_inter)
				* (text->img.bits_per_pixel / 8));
		color = *(unsigned int *)str;
		put_pixel(&mlx->img, nb, x, color);
		x++;
	}
}
