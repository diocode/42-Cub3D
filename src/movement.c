/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:33:05 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/04/04 12:42:22 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int    handle_keys(int keysym, t_data *data)
{
    t_player    *p;
    
    p = data->player;
    if (keysym == XK_Up)
        move_up(data);
    else if (keysym == XK_Down)
        move_down(data);
    else if (keysym == XK_Right)
        move_right(data);
    else if (keysym == XK_Left)
        move_left(data);
    else if (keysym == XK_Escape)
        st_quit(data);*/
        return (0);
}