/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:24:58 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/04/04 12:39:30 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int print_frame(t_data *data)
{
    mlx_destroy_image(data->mlx, data->img.mlx_img);
    data->img.mlx_img = mlx_new_image(data->mlx, S_W, S_H);
    //hook_player(data->player);
    mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, \
	0, 0);
    return (0);   
}

void	render(t_data *data)
{   
    mlx_data_init(data);
    mlx_hook(data->win, KeyRelease, KeyReleaseMask, &handle_keys, data);
    mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &ft_quit, data);
    mlx_loop_hook(data->mlx, print_frame, NULL);
	set_player(data->player);
    mlx_loop(data->mlx);
}
