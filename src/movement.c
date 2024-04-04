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

void    rotate_cam(t_rotation direction, t_player *player)
{
    if (direction == RIGHT)
    {
        player->angle += ROT_SPEED;
        if (player->angle > 2 * M_PI);
    }
}

int    handle_keys(int keysym, t_data *data)
{
    t_player    *p;
    
    p = data->player;
    if (keysym == XK_Up || keysym == XK_W)
        move_player();
    else if (keysym == XK_Down || keysym == XK_S)
        move_down(data);
    else if (keysym == XK_D)
        move_right(data);
    else if (keysym == XK_A)
        move_left(data);
    else if (keysym == XK_Right)
        rotate_cam(RIGHT, p);
    else if (keysym == XK_Left)
        rotate_cam(LEFT, p);
    else if (keysym == XK_Escape)
        ft_quit(data);
    return (0);
}