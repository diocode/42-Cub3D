/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:24:58 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/04/11 17:06:28 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    set_dda(t_raycast *ray, t_data *data)
{
    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->horiz_x = (data->player->pos.x - ray->map_x) * ray->vert_x;
    }
    else
    {
        ray->step_x = 1;
        ray->horiz_x = (data->player->pos.x + 1.0 - ray->map_x) * ray->vert_x;
    }
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->horiz_y = (data->player->pos.y - ray->map_y) * ray->vert_y;
    }
    else
    {
        ray->step_y = 1;
        ray->horiz_y = (data->player->pos.y + 1.0 - ray->map_y) * ray->vert_y;
    }
}

void    do_dda(t_data * data, t_raycast *ray)
{
    int wall;

    wall = 0;
    while (wall == 0)
    {
        if (ray->horiz_x < ray->horiz_y)
        {
            ray->horiz_x += ray->vert_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->horiz_y += ray->vert_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (ray->map_y < 0.25 || ray->map_x < 0.25
            || ray->map_y > data->map->map_height - 0.25
            || ray->map_x > data->map->map_width - 1.25)
            break;
        else if (data->map->layout[ray->map_y][ray->map_x] > '0')
        {
            wall = 1;
        }
    }
}

void    ray_info_init(int x, t_raycast *ray, t_data *data)
{
    raycast_init(data->ray);
    
    ray->ray_angle = 2 * x / (double)WIN_WIDTH - 1;
    ray->dir_x = data->player->dir_x + data->player->plane_x * ray->ray_angle;
    ray->dir_y = data->player->dir_y + data->player->plane_x * ray->ray_angle;
    ray->map_x = data->player->pos.x;
    ray->map_y = data->player->pos.y;
    ray->vert_x = fabs(1 / ray->dir_x);
    ray->vert_y = fabs(1 / ray->dir_y);
}

// this calculates how the wall will be drawn
// calculates the distance to the wall, then with that it calculates how much of the screen will 
// the wall occupy (closer - more)
void    calculate_line_height(t_raycast *ray, t_data *data)
{
    if (ray->side == 0)
        ray->distance = (ray->horiz_x - ray->vert_x);
    else
        ray->distance = (ray->horiz_y - ray->vert_y);
    ray->line_height = (int)(data->win_height / ray->distance);
    ray->draw_start = -(ray->line_height) / 2 + data->win_height / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + data->win_height / 2;
    if (ray->draw_end >= data->win_height)
        ray->draw_end = data->win_height - 1;
    if (ray->side == 0)
        ray->wall = data->player->pos.y + ray->distance * ray->dir_y;
    else
        ray->wall = data->player->pos.x + ray->distance * ray->dir_x;
    ray->wall -= floor(ray->wall);
}

void    cast_rays(t_data *data)
{
    t_raycast   *ray;
    int x;

    x = 0;
    ray = data->ray;
    while (x < data->win_width)
    {
        ray_info_init(x, ray, data);
        set_dda(ray, data);
        do_dda(data, ray);
        calculate_line_height(ray, data);
		update_tex_pixels(data, x);
        x++;
    }
}

int print_frame(t_data *data)
{
	render_img(data);
    return (0);   
}

void	render_ray(t_data *data)
{
	if (!init_tex_pixels(data))
		return ;
    raycast_init(data->ray);
    cast_rays(data);
    render_frame(data);
}

void	render_img(t_data *data)
{
	//if (!handle_textures(data))
	//	return ;
    render_ray(data);
    //cast_rays(data);
    //render_frame(data);
    //set_player(data->player);
    //mlx_hook(data->win, KeyRelease, KeyReleaseMask, &handle_keys, data);
    //mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &ft_quit, data);
}