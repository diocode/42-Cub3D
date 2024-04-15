/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:56:38 by digoncal          #+#    #+#             */
/*   Updated: 2024/04/12 14:26:17 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	init_mlx_img(t_data *data, t_img *image, int width, int height)
{
	init_img(image);
	image->mlx_img = mlx_new_image(data->mlx, width, height);
	if (!image->mlx_img)
		return (ft_putstr_fd("Error: invalid mlx_img init.\n", 2), false);
	image->addr = (int *)mlx_get_data_addr(image->mlx_img, &image->bpp,
			&image->line_len, &image->endian);
	return (true);
}

void	init_img(t_img *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->endian = 0;
	img->line_len = 0;
}

static void	init_map(t_map *map)
{
	map->layout = NULL;
	map->map_height = 0;
	map->map_width = 0;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->f = NULL;
	map->c = NULL;
}

void	raycast_init(t_raycast *raycast)
{
	raycast->ray_angle = 0;
	raycast->dir_x = 0;
	raycast->dir_y = 0;
	raycast->distance = 0;
	raycast->side = 0;
	raycast->map_x = 0;
	raycast->map_y = 0;
	raycast->step_x = 0;
	raycast->step_y = 0;
	raycast->horiz_x = 0;
	raycast->horiz_y = 0;
	raycast->vert_x = 0;
	raycast->vert_y = 0;
	raycast->line_height = 0;
	raycast->draw_start = 0;
	raycast->draw_end = 0;
	raycast->wall = 0;
}

void	init_textures(t_data *data)
{
	data->tex = malloc(sizeof(t_textures));
	if (!data->tex)
	{
		data->tex = NULL;
		return (ft_putstr_fd("Error: malloc execution.\n", 2));
	}
	data->tex->texture_pixels = NULL;
	data->tex->textures = NULL;
	data->tex->cc_floor = 0;
	data->tex->cc_ceiling = 0;
	data->tex->size = TEXTURE_SIZE;
	data->tex->index = 0;
	data->tex->step = 0;
	data->tex->pos = 0;
	data->tex->x = 0;
	data->tex->y = 0;
}

t_player	*player_init(void)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (ft_putstr_fd("Error: Malloc error for player.\n", 2), NULL);
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->pos_x = 0;
	player->pos_y = 0;
	player->angle = M_PI;
	player->dir_x = 0;
	player->dir_y = 0;
	player->move.x = 0;
	player->move.y = 0;
	player->rotate = 0;
	player->moved = 0;
	return (player);
}

void	mlx_data_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ft_putstr_fd("Error: mlx error.\n", 2));
	data->win = mlx_new_window(data->mlx, data->win_height, data->win_width, "- Cub3D -");
	if (!data->win)
		return (ft_putstr_fd("Error: mlx_win error.\n", 2));
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
	data->mlx = NULL;
	data->win = NULL;
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	data->player = player_init();
	init_map(data->map);
	data->ray = malloc(sizeof(t_raycast));
	if (!data->ray)
		return (ft_putstr_fd("Error: malloc execution.\n", 2), NULL);
	init_img(&data->img);
	init_textures(data);
	return (data);
}
