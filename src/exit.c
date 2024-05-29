/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:19:09 by agiraud           #+#    #+#             */
/*   Updated: 2023/10/24 18:02:45 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_map(t_map *map)
{
	free(map->n_text.name);
	free(map->s_text.name);
	free(map->e_text.name);
	free(map->w_text.name);
	free(map->map);
}

int	exit_prog(t_all *pack)
{
	close_mlx(&pack->mlx, &pack->map);
	free_map(&pack->map);
	exit(0);
}
