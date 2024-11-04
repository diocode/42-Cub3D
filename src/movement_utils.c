/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:53:46 by digoncal          #+#    #+#             */
/*   Updated: 2024/11/04 17:53:49 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	move_up(t_data *data)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = data->player->position.x + data->player->dir.x * PLAYER_SPEED;
	new_pos_y = data->player->position.y + data->player->dir.y * PLAYER_SPEED;
	if (valid_move(data, new_pos_x, new_pos_y))
	{
		data->player->position.x = new_pos_x;
		data->player->position.y = new_pos_y;
		return (1);
	}
	return (0);
}

int	move_down(t_data *data)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = data->player->position.x - data->player->dir.x * PLAYER_SPEED;
	new_pos_y = data->player->position.y - data->player->dir.y * PLAYER_SPEED;
	if (valid_move(data, new_pos_x, new_pos_y))
	{
		data->player->position.x = new_pos_x;
		data->player->position.y = new_pos_y;
		return (1);
	}
	return (0);
}

int	move_right(t_data *data)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = data->player->position.x - data->player->dir.y * PLAYER_SPEED;
	new_pos_y = data->player->position.y + data->player->dir.x * PLAYER_SPEED;
	if (valid_move(data, new_pos_x, new_pos_y))
	{
		data->player->position.x = new_pos_x;
		data->player->position.y = new_pos_y;
		return (1);
	}
	return (0);
}

int	move_left(t_data *data)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = data->player->position.x + data->player->dir.y * PLAYER_SPEED;
	new_pos_y = data->player->position.y - data->player->dir.x * PLAYER_SPEED;
	if (valid_move(data, new_pos_x, new_pos_y))
	{
		data->player->position.x = new_pos_x;
		data->player->position.y = new_pos_y;
		return (1);
	}
	return (0);
}
