/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:24:58 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/04/02 13:42:00 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    render(t_data *data)
{
    t_player	*player;
	t_raycast	*raycast;
    
    mlx_data_init(data);
    player = player_init(data->map);
	raycast = raycast_init(data, data->map, player);
    mlx_hook(data->win, KeyRelease, KeyReleaseMask, &handle_keypress, data);
    mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &ft_quit, data);
    mlx_loop(data->mlx);
}