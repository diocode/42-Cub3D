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

static void	draw_floor_ceiling(t_data *data, int ray,
			double bottom_pix, double top_pix)
{
	int	i;

	i = bottom_pix;
	while (i < S_H)
	{
		if (!(ray < 0 || ray >= S_W || i < 0))
		{
			mlx_pixel_put(data->mlx, data->win, ray, i, data->tex->cc_ceiling);
			i++;
		}
	}
	i = 0;
	while (i < top_pix)
	{
		if (!(ray < 0 || ray >= S_W || i < 0 || i >= S_H))
		{
			mlx_pixel_put(data->mlx, data->win, ray, i, data->tex->cc_floor);
			i++;
		}
	}
}

static void	draw_wall(t_data *data, int ray, double top_pix, double bottom_pix)
{
	int	color;

	data->ray->ray_angle = fix_angle(data->ray->ray_angle);
	if (!data->ray->wall)
	{
		if (data->ray->ray_angle > M_PI / 2
			&& data->ray->ray_angle < 3 * (M_PI / 2))
			color = 0xFFFFE000;
		else
			color = 0xFFF00FF0;
	}
	else
	{
		if (data->ray->ray_angle > 0 && data->ray->ray_angle < M_PI)
			color = 0xFFFFA500;
		else
			color = 0xFF0080C0;
	}
	while (top_pix < bottom_pix)
	{
		if (!(ray < 0 || ray >= S_W || top_pix < 0 || top_pix >= S_H))
			mlx_pixel_put(data->mlx, data->win, ray, top_pix, color);
		top_pix++;
	}
}

void	render_wall(t_data *data, int ray)
{
	double	height;
	double	bottom_pix;
	double	top_pix;

	data->ray->distance = cos(fix_angle(data->ray->ray_angle
				- data->player->angle));
	height = (TILE_SIZE / data->ray->distance)
		* ((S_W / 2) / tan(((FOV * M_PI) / 180) / 2));
	bottom_pix = (S_H / 2) + (height / 2);
	top_pix = (S_H / 2) - (height / 2);
	if (bottom_pix > S_H)
		bottom_pix = S_H;
	if (top_pix < 0)
		top_pix = 0;
	data->ray->index = ray;
	draw_wall(data, height, top_pix, bottom_pix);
	draw_floor_ceiling(data, ray, bottom_pix, top_pix);
}
