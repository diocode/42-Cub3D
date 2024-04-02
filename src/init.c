/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:56:38 by digoncal          #+#    #+#             */
/*   Updated: 2024/04/02 13:45:31 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_img(t_data *data)
{
	data->img.mlx_img = NULL;
	data->img.addr = NULL;
	data->img.bpp = 0;
	data->img.endian = 0;
	data->img.line_len = 0;
	data->img.height = 0;
	data->img.width = 0;
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

t_raycast	*raycast_init(t_data *data, t_map *map, t_player *player)
{
	t_raycast	*raycast;

	(void)data;
	(void)map;
	(void)player;
	raycast = malloc(sizeof(t_raycast));
	if (!raycast)
		printf("malloc error\n");
	return (NULL);
}

t_player	*player_init(void)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
	{
		printf("Malloc error for player\n");
		return (NULL);
	}
	//ft_memset(player, 0, sizeof(t_player));
	//player->angle = angle(map->layout);
	player->map_pos.x = 0;
	player->map_pos.y = 0;
	player->speed = 1.0;
	player->angle = 0;
	player->front = 0;
	player->back = 0;
	player->left = 0;
	player->right = 0;
	return (player);
}

void	mlx_data_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		printf("error!\n");
	data->win = mlx_new_window(data->mlx, 780, 780, "cube_3d");
	if (!data->win)
		printf("mlx_win error\n");
	data->img.mlx_img = mlx_new_image(data->mlx, 780, 780);
	if (!data->img.mlx_img)
		printf("mlx_img error!\n");
	data->img.addr = (int *)mlx_get_data_addr(data->img.mlx_img, \
	&data->img.bpp, &data->img.line_len, &data->img.endian);
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
	init_img(data);
	data->player = player_init();
	init_map(data->map);
	//render(data);
	/*mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, \
	0, 0);*/
	data->win = 0;
	return (data);
}
