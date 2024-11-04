/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:28:07 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/11/04 18:12:43 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->tex->texture_pixels[y][x] > 0)
		image->addr[y * (image->line_len / 4) + x] \
			= data->tex->texture_pixels[y][x];
	else if (y < WIN_HEIGHT / 2)
		image->addr[y * (image->line_len / 4) + x] = data->map_info->cc_ceiling;
	else if (y < WIN_HEIGHT - 1)
		image->addr[y * (image->line_len / 4) + x] = data->map_info->cc_floor;
}

static void	render_frame(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	image.mlx_img = NULL;
	if (!init_mlx_img(data, &image, WIN_WIDTH, WIN_HEIGHT))
		return ;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			set_frame_image_pixel(data, &image, x, y);
	}
	mlx_put_image_to_window(data->mlx, data->win, image.mlx_img, 0, 0);
	mlx_destroy_image(data->mlx, image.mlx_img);
}

void	render(t_data *data)
{
	if (!init_tex_pixels(data))
		return ;
	raycast(data);
	render_frame(data);
}

int	render_game(t_data *data)
{
	data->player->moved += move_player(data);
	if (data->player->moved == 0)
		return (EXIT_SUCCESS);
	render(data);
	return (EXIT_FAILURE);
}
