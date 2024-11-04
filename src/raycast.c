/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:28:31 by digoncal          #+#    #+#             */
/*   Updated: 2024/07/18 18:29:43 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	line_height(t_data *data, t_raycast *ray)
{
	if (!ray->side)
		ray->wall_dist = ray->next_dist.x - ray->grid_dist.x;
	else
		ray->wall_dist = ray->next_dist.y - ray->grid_dist.y;
	ray->line_height = (int)(WIN_WIDTH / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	if (!ray->side)
		ray->wall_tex = data->player->position.y + ray->wall_dist * ray->dir.y;
	else
		ray->wall_tex = data->player->position.x + ray->wall_dist * ray->dir.x;
	ray->wall_tex -= floor(ray->wall_tex);
}

static void	run_dda(t_data *data, t_raycast *ray)
{
	while (!ray->hit)
	{
		if (ray->next_dist.x < ray->next_dist.y)
		{
			ray->next_dist.x += ray->grid_dist.x;
			ray->map_x += ray->step_x;
			ray->side = false;
		}
		else
		{
			ray->next_dist.y += ray->grid_dist.y;
			ray->map_y += ray->step_y;
			ray->side = true;
		}
		if (data->map[ray->map_y][ray->map_x] == '1')
			ray->hit = true;
	}
}

static void	calculate_dda(t_data *data, t_raycast *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->next_dist.x = (data->player->position.x - ray->map_x)
			* ray->grid_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->next_dist.x = (ray->map_x + 1.0 - data->player->position.x)
			* ray->grid_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->next_dist.y = (data->player->position.y - ray->map_y)
			* ray->grid_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->next_dist.y = (ray->map_y + 1.0 - data->player->position.y)
			* ray->grid_dist.y;
	}
}

static void	init_ray(t_data *data, t_raycast *ray, int x)
{
	double	cam_x;

	cam_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir.x = data->player->dir.x + data->player->cam.x * cam_x;
	ray->dir.y = data->player->dir.y + data->player->cam.y * cam_x;
	ray->grid_dist.x = fabs(1 / ray->dir.x);
	ray->grid_dist.y = fabs(1 / ray->dir.y);
	ray->hit = false;
	ray->side = false;
	ray->map_x = (int)data->player->position.x;
	ray->map_y = (int)data->player->position.y;
	ray->wall_dist = 0;
	ray->wall_tex = 0;
}

void	raycast(t_data *data)
{
	int	x;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		init_ray(data, data->ray, x);
		calculate_dda(data, data->ray);
		run_dda(data, data->ray);
		line_height(data, data->ray);
		update_tex_pixels(data, data->ray, x);
	}
}
