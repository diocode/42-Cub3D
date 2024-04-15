/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:33:05 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/04/12 14:48:14 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	rotate_player(t_data *data, double dir)
{
	double	tmp;
	double	rot_speed;

	rot_speed = dir * ROT_SPEED;
	tmp = data->player->dir_x;
	data->player->dir_x = data->player->dir_x \
		* cos(rot_speed) - data->player->dir_y * sin(rot_speed);
	data->player->dir_y = tmp * sin(rot_speed) \
		+ data->player->dir_y * cos(rot_speed);
	tmp = data->player->plane_x;
	data->player->plane_x = data->player->plane_x \
		* cos(rot_speed) - data->player->plane_y * sin(rot_speed);
	data->player->plane_y = tmp * sin(rot_speed) + data->player->plane_y \
		* cos(rot_speed);
	return (1);
}

static bool	valid_move(t_data *data, double x, double y)
{
	if (x < 0.25 || x >= data->map->map_width - 1.25)
		return (false);
	if (y < 0.25 || y >= data->map->map_height - 0.25)
		return (false);
	if (data->map->layout[(int)y][(int)x] == '1'
		|| data->map->layout[(int)y][(int)x] == ' ')
		return (false);
	return (true);
}

int move_up(t_data *data)
{
	double	new_pos_x;
	double	 new_pos_y;

	new_pos_x = data->player->pos_x + data->player->dir_x * PLAYER_SPEED;
	new_pos_y = data->player->pos_y + data->player->dir_y * PLAYER_SPEED;
	if (valid_move(data, new_pos_x, new_pos_y))
	{
		data->player->pos_x = new_pos_x;
		data->player->pos_y =  new_pos_y;
		return (1);
	}
	return (0);
}

int move_down(t_data *data)
{
	double	new_pos_x;
	double	 new_pos_y;

	new_pos_x = data->player->pos_x - data->player->dir_x * PLAYER_SPEED;
	new_pos_y = data->player->pos_y - data->player->dir_y * PLAYER_SPEED;
	if (valid_move(data, new_pos_x, new_pos_y))
	{
		data->player->pos_x = new_pos_x;
		data->player->pos_y = new_pos_y;
		return (1);
	}
	return (0);
}

int move_right(t_data *data)
{
	double	new_pos_x;
	double	 new_pos_y;

	new_pos_x = data->player->pos_x - data->player->dir_y * PLAYER_SPEED;
	new_pos_y = data->player->pos_y + data->player->dir_x * PLAYER_SPEED;
	if (valid_move(data, new_pos_x, new_pos_y))
	{
		data->player->pos_x = new_pos_x;
		data->player->pos_y = new_pos_y;
		return (1);
	}
	return (0);
}

int	move_left(t_data *data)
{
	double	new_pos_x;
	double	 new_pos_y;

	new_pos_x = data->player->pos_x + data->player->dir_y * PLAYER_SPEED;
	new_pos_y = data->player->pos_y - data->player->dir_x * PLAYER_SPEED;
	if (valid_move(data, new_pos_x, new_pos_y))
	{
		data->player->pos_x = new_pos_x;
		data->player->pos_y = new_pos_y;
		return (1);
	}
	return (0);
}

bool	move_player(t_data *data)
{
	int move;

	move = 0;
	if (data->player->move.y == 1)
		move += move_up(data);
	if (data->player->move.y == -1)
		move += move_down(data);
	if (data->player->move.x == 1)
		move += move_right(data);
	if (data->player->move.x == -1)
		move += move_left(data);
	if (data->player->rotate != 0)
		move += rotate_player(data, data->player->rotate);
	return (move);
}
