/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:56:38 by digoncal          #+#    #+#             */
/*   Updated: 2024/03/25 13:56:38 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_img(t_data *data)
{
	data->img.mlx_img = NULL;
	data->img.addr = NULL;
	data->img.bpp = 0;
	data->img.endian = 0;
	data->img.line_len = 0;
}

static void	init_map(t_map *map)
{
	map->layout = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->f = NULL;
	map->c = NULL;
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd("Error: malloc execution.\n", 2), NULL);
	data->map = malloc(sizeof(t_map));
	if (!data->map)
	{
		free_data(data);
		return (ft_putstr_fd("Error: malloc execution.\n", 2), NULL);
	}
	init_map(data->map);
	data->mlx = 0;
	data->win = 0;
	init_img(data);
	return (data);
}
