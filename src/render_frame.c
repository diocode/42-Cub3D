/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:08:30 by digoncal          #+#    #+#             */
/*   Updated: 2024/04/04 14:23:57 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	fix_angle(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 0)
		angle -= 2 * M_PI;
	return (angle);
}

static void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->line_len / 4) + x;
	image->addr[pixel] = color;
}

static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->tex->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, data->tex->texture_pixels[y][x]);
	else if (y < S_H / 2)
		set_image_pixel(image, x, y, data->tex->cc_ceiling);
	else if (y < S_H -1)
		set_image_pixel(image, x, y, data->tex->cc_floor);
}

void	render_frame(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	image.mlx_img = NULL;
	if (!init_mlx_img(data, &image, S_W, S_H))
		return ;
	y = 0;
	while (y < S_H)
	{
		x = 0;
		while (x < S_W)
		{
			set_frame_image_pixel(data, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, image.mlx_img, 0, 0);
	mlx_destroy_image(data->mlx, image.mlx_img);
}
