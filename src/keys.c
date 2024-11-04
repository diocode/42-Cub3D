/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:47:26 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/07/22 18:21:41 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mouse_handle(int x, int y, t_data *data)
{
	int	moved;

	moved = 0;
	if (x != WIN_WIDTH / 2)
	{
		if (x < WIN_WIDTH / 2)
			data->player->moved = rotate_player(data, -1, WIN_WIDTH / 2 - x);
		else if (x > WIN_WIDTH / 2)
			data->player->moved = rotate_player(data, 1, x - WIN_WIDTH / 2);
		moved = 1;
	}
	mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, y);
	return (moved);
}

int	handle_key_release(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_quit(data);
	if (keysym == XK_w && data->player->move_y >= 1)
		data->player->move_y = 0;
	if (keysym == XK_s && data->player->move_y <= -1)
		data->player->move_y = 0;
	if (keysym == XK_d && data->player->move_x >= 1)
		data->player->move_x = 0;
	if (keysym == XK_a && data->player->move_x <= -1)
		data->player->move_x = 0;
	if (keysym == XK_Right && data->player->rotate >= -1)
		data->player->rotate = 0;
	if (keysym == XK_Left && data->player->rotate <= 1)
		data->player->rotate = 0;
	data->player->moved = 0;
	return (EXIT_SUCCESS);
}

int	handle_key_press(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_quit(data);
	if (keysym == XK_w)
		data->player->move_y += 1;
	if (keysym == XK_s)
		data->player->move_y += -1;
	if (keysym == XK_d)
		data->player->move_x += 1;
	if (keysym == XK_a)
		data->player->move_x += -1;
	if (keysym == XK_Right)
		data->player->rotate += 1;
	if (keysym == XK_Left)
		data->player->rotate += -1;
	return (EXIT_SUCCESS);
}
