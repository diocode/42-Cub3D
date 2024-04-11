/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:56:38 by digoncal          #+#    #+#             */
/*   Updated: 2024/04/05 13:24:58 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	init_mlx_img(t_data *data, t_img *image, int width, int height)
{
	init_img(image);
	image->mlx_img = mlx_new_image(data->mlx, width, height);
	if (image->mlx_img == NULL)
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

t_raycast	*raycast_init(void)
{
	t_raycast	*raycast;

	raycast = (t_raycast *)malloc(sizeof(t_raycast));
	if (!raycast)
		return (NULL);
	raycast->ray_angle = 0;
	raycast->distance = 0;
	raycast->wall = 0;
	raycast->index = 0;
	raycast->horiz_x = 0;
	raycast->horiz_y = 0;
	raycast->vert_x = 0;
	raycast->vert_y = 0;
	raycast->wall_x = 0;
	raycast->wall_y = 0;
	raycast->dir_x = 0;
	raycast->dir_y = 0;
	raycast->line_height = 0;
	raycast->draw_start = 0;
	raycast->draw_end = 0;
	return (raycast);
}

void	init_textures(t_data *data)
{
	data->tex = malloc(sizeof(t_textures));
	if (!data->tex)
	{
		data->tex = NULL;
		return ;
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
	{
		printf("Malloc error for player\n");
		return (NULL);
	}
	player->pos.x = 0;
	player->pos.y = 0;
	player->fov = (float)(FOV * M_PI) / 180;
	player->angle = M_PI;
	player->dir_x = 0;
	player->dir_y = 0;
	player->move.x = 0;
	player->move.y = 0;
	player->rotate = 0;
	return (player);
}

void	mlx_data_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		printf("error!\n");
	data->win = mlx_new_window(data->mlx, 780, 780, "- Cub3D -");
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
	init_img(&data->img);
	init_map(data->map);
	init_textures(data);
	mlx_data_init(data);
	data->player = player_init();
	data->ray = raycast_init();
	return (data);
}
