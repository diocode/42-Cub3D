/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:44:10 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/11/05 15:19:13 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	init_mlx_img(t_data *data, t_img *img, int width, int height)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->endian = 0;
	img->line_len = 0;
	img->mlx_img = mlx_new_image(data->mlx, width, height);
	if (!img->mlx_img)
		return (ft_putstr_fd("Error\ninvalid mlx_img init.\n", 2), false);
	img->addr = (int *)mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
	return (true);
}

static void	init_player(t_data	*data)
{
	data->player->moved = 0;
	data->player->rotate = 0;
	data->player->move_x = 0;
	data->player->move_y = 0;
}

void	init_mlx(t_data *data)
{
	t_img	screen_img;

	data->mlx = mlx_init();
	if (!data->mlx)
		return (ft_putstr_fd("Error\nmlx init\n", 2));
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data->win)
		return (ft_putstr_fd("Error\nmlx_win\n", 1));
	screen_img.mlx_img = mlx_new_image(data->mlx, WIN_HEIGHT, WIN_WIDTH);
	screen_img.addr = (int *)mlx_get_data_addr(screen_img.mlx_img,
			&screen_img.bpp, &screen_img.line_len, &screen_img.endian);
	data->img = screen_img;
}

void	init_game(t_data *data)
{
	mlx_hook(data->win, KeyPress, KeyPressMask, &handle_key_press, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &handle_key_release, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &ft_quit, data);
	mlx_hook(data->win, MotionNotify, PointerMotionMask, &mouse_handle, data);
	mlx_loop_hook(data->mlx, render_game, data);
	mlx_loop(data->mlx);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd("Error\nmalloc execution.\n", 2), NULL);
	data->mlx = NULL;
	data->win = NULL;
	data->map = NULL;
	data->img.mlx_img = NULL;
	data->map_info = ft_calloc(1, sizeof(t_map_info));
	if (!data->map_info)
		return (ft_putstr_fd("Error\nmalloc execution.\n", 2), NULL);
	data->ray = ft_calloc(1, sizeof(t_raycast));
	if (!data->ray)
		return (ft_putstr_fd("Error\nmalloc execution.\n", 2), NULL);
	data->tex = ft_calloc(1, sizeof(t_textures));
	if (!data->tex)
		return (ft_putstr_fd("Error\nmallos execution.\n", 2), NULL);
	init_textures(data);
	data->player = ft_calloc(1, sizeof(t_player));
	if (!data->player)
		return (ft_putstr_fd("Error\nmalloc execution.\n", 2), NULL);
	init_player(data);
	init_mlx(data);
	return (data);
}
