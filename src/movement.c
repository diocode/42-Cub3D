/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:33:05 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/04/04 14:10:27 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	rotate_cam(t_data *data, double rot_speed)
{
	double	tmp;

	tmp = data->player->dir_x;
	data->player->angle += rot_speed;
	data->player->dir_x = data->player->dir_x \
		* cos(rot_speed) - data->player->dir_y * sin(rot_speed);
	data->player->dir_y = tmp * sin(rot_speed) \
		+ data->player->dir_y * cos(rot_speed);
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

bool	move_player(t_data *data)
{
	double	new_pos_x;
	double	new_pos_y;
	bool	moved;

	moved = false;
	if (data->player->rotate != 0)
	{
		rotate_cam(data, ROT_SPEED * data->player->rotate);
		moved = true;
	}
	new_pos_x = data->player->pos.x + data->player->move.x * PLAYER_SPEED;
	new_pos_y = data->player->pos.y + data->player->move.y * PLAYER_SPEED;
	if (valid_move(data, new_pos_x, new_pos_y))
	{
		data->player->pos.x = (int)new_pos_x;
		data->player->pos.y = (int)new_pos_y;
		moved = true;
	}
	return (moved);
}

int	keyrelease_handle(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_quit(data);
	if (keysym == XK_Right && data->player->rotate == -1)
		data->player->rotate = 0;
	if (keysym == XK_Left && data->player->rotate == 1)
		data->player->rotate = 0;
	if ((keysym == XK_Up || keysym == XK_W) && data->player->move.y == 1)
		data->player->move.y = 0;
	if ((keysym == XK_Down || keysym == XK_S) && data->player->move.y == -1)
		data->player->move.y = -1;
	if (keysym == XK_D && data->player->move.x == 1)
		data->player->move.x -= 1;
	if (keysym == XK_A && data->player->move.x == -1)
		data->player->move.x += 1;
	return (0);
}

int	keypress_handle(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_quit(data);
	if (keysym == XK_Right)
		data->player->rotate = 1;
	if (keysym == XK_Left)
		data->player->rotate = -1;
	if (keysym == XK_Up || keysym == XK_W)
		data->player->move.y = 1;
	if (keysym == XK_Down || keysym == XK_S)
		data->player->move.y = -1;
	if (keysym == XK_D)
		data->player->move.x = 1;
	if (keysym == XK_A)
		data->player->move.x = -1;
	return (0);
}
