/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:44:18 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/07/22 17:13:04 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	rotate_player(t_data *data, double dir, int dist)
{
	double	tmp;
	double	rot_speed;

	if (dist == 0)
		rot_speed = dir * ROT_SPEED * 5;
	else
		rot_speed = (dir * ROT_SPEED) * dist;
	tmp = data->player->dir.x;
	data->player->dir.x = data->player->dir.x \
		* cos(rot_speed) - data->player->dir.y * sin(rot_speed);
	data->player->dir.y = tmp * sin(rot_speed) \
		+ data->player->dir.y * cos(rot_speed);
	tmp = data->player->cam.x;
	data->player->cam.x = data->player->cam.x \
		* cos(rot_speed) - data->player->cam.y * sin(rot_speed);
	data->player->cam.y = tmp * sin(rot_speed) + data->player->cam.y \
		* cos(rot_speed);
	return (1);
}

bool	valid_move(t_data *data, double x, double y)
{
	if (x < 0.25 || x >= WIN_WIDTH - 1.25)
		return (false);
	if (y < 0.25 || y >= WIN_HEIGHT - 0.25)
		return (false);
	if (data->map[(int)y][(int)x] == '1')
		return (false);
	return (true);
}

int	move_player(t_data *data)
{
	int	move;

	move = 0;
	if (data->player->move_y == 1)
		move += move_up(data);
	if (data->player->move_y == -1)
		move += move_down(data);
	if (data->player->move_x == 1)
		move += move_right(data);
	if (data->player->move_x == -1)
		move += move_left(data);
	if (data->player->rotate != 0)
		move += rotate_player(data, data->player->rotate, 0);
	return (move);
}
