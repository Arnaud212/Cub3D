/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:46:28 by agiraud           #+#    #+#             */
/*   Updated: 2023/10/30 17:26:13 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	close_mlx(t_mlx *mlx, t_map *map)
{
	if (map)
	{
		if (map->n_text.img.img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, map->n_text.img.img_ptr);
		if (map->s_text.img.img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, map->s_text.img.img_ptr);
		if (map->e_text.img.img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, map->e_text.img.img_ptr);
		if (map->w_text.img.img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, map->w_text.img.img_ptr);
	}
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
}

int	get_textures_2(t_text *text, t_mlx *mlx)
{
	text->img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
			text->name, &text->width, &text->height);
	if (!text->img.img_ptr)
		return (1);
	text->img.addr = mlx_get_data_addr(text->img.img_ptr,
			&text->img.bits_per_pixel, &text->img.line_length,
			&text->img.endian);
	if (!text->img.addr)
		return (1);
	return (0);
}

int	get_textures(t_mlx *mlx, t_map *map)
{
	if (get_textures_2(&map->n_text, mlx))
		return (error_msg("Failed north texture"));
	if (get_textures_2(&map->s_text, mlx))
		return (error_msg("Failed south texture"));
	if (get_textures_2(&map->e_text, mlx))
		return (error_msg("Failed east texture"));
	if (get_textures_2(&map->w_text, mlx))
		return (error_msg("Failed west texture"));
	free(map->n_text.name);
	free(map->s_text.name);
	free(map->e_text.name);
	free(map->w_text.name);
	map->n_text.name = NULL;
	map->s_text.name = NULL;
	map->e_text.name = NULL;
	map->w_text.name = NULL;
	return (0);
}

int	launch_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (-1);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (!mlx->win_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		return (-1);
	}
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->img.img_ptr)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		return (-1);
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr,
			&mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	if (!mlx->img.addr)
		return (-1);
	return (0);
}
