/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:08:30 by digoncal          #+#    #+#             */
/*   Updated: 2024/04/12 14:38:01 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->tex->texture_pixels[y][x] > 0)
		image->addr[y * (image->line_len / 4) + x] = data->tex->texture_pixels[y][x];
	else if (y < data->win_height / 2)
		image->addr[y * (image->line_len / 4) + x] = data->tex->cc_ceiling;
	else if (y < data->win_height - 1)
		image->addr[y * (image->line_len / 4) + x] = data->tex->cc_floor;
}

void	render_frame(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	image.mlx_img = NULL;
	if (!init_mlx_img(data, &image, data->win_width, data->win_height))
		return ;
	y = -1;
	while (++y < data->win_height)
	{
		x = -1;
		while (++x < data->win_width)
			set_frame_image_pixel(data, &image, x, y);
	}
	mlx_put_image_to_window(data->mlx, data->win, image.mlx_img, 0, 0);
	mlx_destroy_image(data->mlx, image.mlx_img);
}
