/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraud <agiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:41:17 by agiraud           #+#    #+#             */
/*   Updated: 2023/10/30 17:56:41 by agiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	turn_left(t_player *player)
{
	double	temp_x;

	temp_x = player->dir_x;
	player->dir_x = player->dir_x * COS_A + player->dir_y * SIN_A;
	player->dir_y = player->dir_y * COS_A - temp_x * SIN_A;
	player->plane_x = -player->dir_y * FOV;
	player->plane_y = player->dir_x * FOV;
}

int	key_press(int key, t_all *pack)
{
	if (key != XK_Escape && key != XK_w && key != XK_s
		&& key != XK_a && key != XK_d && key != XK_Up
		&& key != XK_Down && key != XK_Left && key != XK_Right)
		return (0);
	if (key == XK_Escape)
	{
		printf("Good bye !!!\n");
		exit_prog(pack);
	}
	if (key == XK_w || key == XK_Up)
		pack->player.mv_forth = 1;
	if (key == XK_s || key == XK_Down)
		pack->player.mv_back = 1;
	if (key == XK_a)
		pack->player.mv_left = 1;
	if (key == XK_d)
		pack->player.mv_right = 1;
	if (key == XK_Left)
		pack->player.turn_left = 1;
	if (key == XK_Right)
		pack->player.turn_right = 1;
	return (0);
}

int	key_release(int key, t_all *pack)
{
	if (key != XK_w && key != XK_s && key != XK_a
		&& key != XK_d && key != XK_Up && key != XK_Down
		&& key != XK_Left && key != XK_Right)
		return (0);
	if (key == XK_w || key == XK_Up)
		pack->player.mv_forth = 0;
	if (key == XK_s || key == XK_Down)
		pack->player.mv_back = 0;
	if (key == XK_a)
		pack->player.mv_left = 0;
	if (key == XK_d)
		pack->player.mv_right = 0;
	if (key == XK_Left)
		pack->player.turn_left = 0;
	if (key == XK_Right)
		pack->player.turn_right = 0;
	return (0);
}

int	refresh(t_all *pack)
{
	if (pack->player.mv_forth)
		mv_up(&pack->player, &pack->map);
	if (pack->player.mv_back)
		mv_down(&pack->player, &pack->map);
	if (pack->player.mv_left)
		mv_left(&pack->player, &pack->map);
	if (pack->player.mv_right)
		mv_right(&pack->player, &pack->map);
	if (pack->player.turn_right)
		turn_right(&pack->player);
	if (pack->player.turn_left)
		turn_left(&pack->player);
	frame(&pack->mlx, &pack->player, &pack->map);
	return (0);
}
