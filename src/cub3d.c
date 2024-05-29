/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:51:37 by agiraud           #+#    #+#             */
/*   Updated: 2023/10/30 18:04:22 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <unistd.h>

int	error_msg(char *error)
{
	ft_putendl_fd("Error", STDOUT_FILENO);
	ft_putendl_fd(error, STDOUT_FILENO);
	return (1);
}

void	start_loop(t_all *pack)
{
	frame(&pack->mlx, &pack->player, &pack->map);
	mlx_hook(pack->mlx.win_ptr, KeyPress, KeyPressMask, key_press, pack);
	mlx_hook(pack->mlx.win_ptr, KeyRelease, KeyReleaseMask, key_release, pack);
	mlx_hook(pack->mlx.win_ptr, DestroyNotify, NoEventMask, exit_prog, pack);
	mlx_loop_hook(pack->mlx.mlx_ptr, refresh, pack);
	mlx_loop(pack->mlx.mlx_ptr);
	close_mlx(&pack->mlx, &pack->map);
	free_map(&pack->map);
}

int	verif_file(t_map *map)
{
	int	fd;

	fd = open(map->n_text.name, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(map->s_text.name, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(map->e_text.name, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(map->w_text.name, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	handle(t_all *pack)
{
	if (launch_mlx(&pack->mlx))
	{
		free_map(&pack->map);
		return (1);
	}
	if (get_textures(&pack->mlx, &pack->map))
	{
		free_map(&pack->map);
		close_mlx(&pack->mlx, &pack->map);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_all	pack;

	init_map(&pack.map);
	init_player(&pack.player);
	if (parse(argc, argv, &pack.map, &pack.player))
	{
		free_map(&pack.map);
		return (1);
	}	
	if (verif_file(&pack.map))
	{
		error_msg("Failed  texture");
		free_map(&pack.map);
		return (1);
	}
	if (handle(&pack))
		return (1);
	start_loop(&pack);
	return (0);
}
