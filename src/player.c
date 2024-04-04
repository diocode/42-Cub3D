/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:02:25 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/04/04 11:57:12 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>


void    set_player(t_player *player)
{
    player->pos.x = player->pos.x * TILE_SIZE + TILE_SIZE / 2;
    player->pos.y = player->pos.y * TILE_SIZE + TILE_SIZE / 2;
    player->fov = (FOV * M_PI) / 180;
    player->angle = M_PI;
}