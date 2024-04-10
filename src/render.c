/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:24:58 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/04/04 17:58:24 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int unit_circle(float angle, char c) // check the unit circle
{
    if (c == 'x')
    {
        if (angle > 0 && angle < M_PI)
            return (1);
    }
    else if (c == 'y')
    {
        if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
            return (1);
    }
    return (0);
}

int check_intersection(float angle, float *inter, float *tile, int horizontal)
{
    if (horizontal)
    {
        if (angle > 0 && angle < M_PI)
        {
            *inter += TILE_SIZE;
            return (-1);
        }
        *tile *= -1;
    }
    else
    {
        if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
        {
            *inter += TILE_SIZE;
            return (-1);
        }
        *tile *= -1;
    }
    return (1);
}

//check if the "coordinate" is a wall
int hit_wall(float x, float y, t_data *data)
{
    int x_map;
    int y_map;

    if ( x < 0 || y < 0)
        return (0);
    x_map = floor(x / TILE_SIZE);
    y_map = floor(y / TILE_SIZE);
    if ((y_map >= data->map->map_height) || x_map >= data->map->map_width)
        return (0);
    if (data->map->layout[y_map] && x_map <= (int)ft_strlen(data->map->layout[y_map]))
        if (data->map->layout[y_map][x_map] == '1')
            return (0);
    return (1);
}

float   get_vertical(t_data *data, float angle)
{
    float   v_x;
    float   v_y;
    int     pixel;
    float   x_tile;
    float   y_tile;

    x_tile = TILE_SIZE;
    y_tile = TILE_SIZE / tan(angle);
    v_x = floor(data->player->pos.x / TILE_SIZE) * TILE_SIZE;
    pixel = check_intersection(angle, &v_x, &x_tile, 0);
    v_y = data->player->pos.y + (v_x - data->player->pos.x) / tan(angle);
    if ((unit_circle(angle, 'x') && x_tile > 0)
        || (!unit_circle(angle, 'x') && x_tile < 0))
        x_tile *= -1;
    while (hit_wall(v_x - pixel, v_y, data))
    {
        v_x += x_tile;
        v_y += y_tile;
    }
	data->ray->vert_x = v_x;
	data->ray->vert_y = v_y;
    return (sqrt(pow(v_x - data->player->pos.x, 2) + pow(v_y - data->player->pos.y, 2)));
}

float   get_horizontal(t_data *data, float angle)
{
    float   h_x;
    float   h_y;
    int     pixel;
    float   x_tile;
    float   y_tile;

    y_tile = TILE_SIZE;
    x_tile = TILE_SIZE / tan(angle);
    h_y = floor(data->player->pos.y / TILE_SIZE) * TILE_SIZE;
    pixel = check_intersection(angle, &h_y, &y_tile, 1);
    h_x = data->player->pos.x + (h_y - data->player->pos.y) / tan(angle);
    if ((unit_circle(angle, 'y') && x_tile > 0)
        || (!unit_circle(angle, 'y') && x_tile < 0))
        x_tile *= -1;
    while (hit_wall(h_x, h_y - pixel, data))
    {
        h_x += x_tile;
        h_y += y_tile;
    }
	data->ray->horiz_x = h_x;
	data->ray->horiz_y = h_y;
    return (sqrt(pow(h_x - data->player->pos.x, 2) + pow(h_y - data->player->pos.y, 2)));
}

//
void    cast_rays(t_data *data)
{
    double  hor_inter;//horizontal intersection
    double  ver_inter;//vertical intersection
    int ray;

    ray = 0;
    data->ray->ray_angle = data->player->angle - (data->player->fov / 2); //start angle
    while (ray < S_W)
    {
        data->ray->wall = 0;
        hor_inter = get_horizontal(data, (float)fix_angle(data->ray->ray_angle));
        ver_inter = get_vertical(data, (float)fix_angle(data->ray->ray_angle));
        if (ver_inter <= hor_inter) //check distance
            data->ray->distance = ver_inter;
        else
        {
            data->ray->distance = hor_inter;
            data->ray->wall = 1;
        }
		update_tex_pixels(data, ray);
        //render_wall(data, ray);
        ray++;
        data->ray->ray_angle += (data->player->fov / S_W);
    }
}

int print_frame(t_data *data)
{
    //mlx_destroy_image(data->mlx, data->img.mlx_img);
    data->img.mlx_img = mlx_new_image(data->mlx, S_W, S_H);
    //hook_player(data->player);
	if (!init_tex_pixels(data))
		return (1);
	cast_rays(data);
	render_frame(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, \
	0, 0);
    return (0);   
}

void	render(t_data *data)
{
    mlx_data_init(data);
	if (!move_player(data))
		return ;
    //set_player(data->player);
	mlx_hook(data->win, KeyPress, KeyPressMask, &keypress_handle, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &keyrelease_handle, data);
    mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &ft_quit, data);
    mlx_loop_hook(data->mlx, print_frame, NULL);
    mlx_loop(data->mlx);
}
