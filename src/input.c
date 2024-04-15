/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:42:28 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/04/12 14:10:37 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    check_input(t_data *data)
{
    mlx_hook(data->win, KeyPress, KeyPressMask, &keypress_handle, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &keyrelease_handle, data);
    mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &ft_quit, data);
}

int	keyrelease_handle(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_quit(data);
	if (keysym == XK_Right && data->player->rotate >= -1)
		data->player->rotate = 0;
	if (keysym == XK_Left && data->player->rotate <= 1)
		data->player->rotate = 0;
	if (keysym == XK_w && data->player->move.y == 1)
		data->player->move.y = 0;
	if (keysym == XK_s && data->player->move.y == -1)
		data->player->move.y = 0;
	if (keysym == XK_d && data->player->move.x == 1)
		data->player->move.x -= 1;
	if (keysym == XK_a && data->player->move.x == -1)
		data->player->move.x += 1;
	return (0);
}

int	keypress_handle(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_quit(data);
	if (keysym == XK_Right)
		data->player->rotate += 1;
	if (keysym == XK_Left)
		data->player->rotate -= 1;
	if (keysym == XK_w)
		data->player->move.y = 1;
	if (keysym == XK_s)
		data->player->move.y = -1;
	if (keysym == XK_d)
		data->player->move.x = 1;
	if (keysym == XK_a)
		data->player->move.x = -1;
	return (0);
}
