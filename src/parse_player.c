/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:57:41 by digoncal          #+#    #+#             */
/*   Updated: 2024/07/22 17:18:51 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	save_player(t_data *data, char **map, int y, int x)
{
	data->player->position.x = x;
	data->player->position.y = y;
	if (map[y][x] == 'N')
	{
		data->player->dir = (t_pos){0, -1.01};
		data->player->cam = (t_pos){0.66, 0};
	}
	else if (map[y][x] == 'S')
	{
		data->player->dir = (t_pos){0, 1.01};
		data->player->cam = (t_pos){-0.66, 0};
	}
	else if (map[y][x] == 'W')
	{
		data->player->dir = (t_pos){-1.01, 0};
		data->player->cam = (t_pos){0, -0.66};
	}
	else if (map[y][x] == 'E')
	{
		data->player->dir = (t_pos){1.01, 0};
		data->player->cam = (t_pos){0, 0.66};
	}
}

bool	parse_player(t_data *data, char **map)
{
	t_pos	pos;
	int		players;

	players = 0;
	if (!data->player)
		return (ft_putstr_fd("Error: invalid player.\n", 2), false);
	pos.y = -1;
	while (map[(int)++pos.y])
	{
		pos.x = -1;
		while (map[(int)pos.y][(int)++pos.x])
		{
			if (map[(int)pos.y][(int)pos.x] == 'N'
					|| map[(int)pos.y][(int)pos.x] == 'S'
					|| map[(int)pos.y][(int)pos.x] == 'W'
					|| map[(int)pos.y][(int)pos.x] == 'E')
			{
				save_player(data, map, (int)pos.y, (int)pos.x);
				players++;
			}
		}
	}
	if (players == 1)
		return (true);
	return (ft_putstr_fd("Error: invalid player.\n", 2), false);
}
