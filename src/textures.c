/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:31:31 by digoncal          #+#    #+#             */
/*   Updated: 2024/04/12 16:24:49 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	init_texture_img(t_data *data, t_img *image, char *path)
{
	image->addr = NULL;
	image->bpp = 0;
	image->line_len = 0;
	image->endian = 0;
	image->mlx_img = mlx_xpm_file_to_image(data->mlx, path, &data->tex->size, \
		&data->tex->size);
	if (!image->mlx_img)
		return (ft_putstr_fd("Error: minilibx failed.\n", 2), true);
	image->addr = (int *) mlx_get_data_addr(image->mlx_img, &image->bpp, \
		&image->line_len, &image->endian);
	return (false);
}

static int	*xpm_to_img(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	if (init_texture_img(data, &tmp, path))
		return (NULL);
	buffer = ft_calloc(1, sizeof * buffer * data->tex->size * data->tex->size);
	if (!buffer)
		return (ft_putstr_fd("Error: invalid malloc.\n", 2), NULL);
	y = 0;
	while (y < data->tex->size)
	{
		x = 0;
		while (x < data->tex->size)
		{
			buffer[y * data->tex->size + x] = tmp.addr[y * data->tex->size + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.mlx_img);
	return (buffer);
}

bool	handle_textures(t_data *data)
{
	if (!data->tex)
		return (ft_putstr_fd("Error: textures not found.\n", 2), false);
	data->tex->cc_ceiling = rgb_to_int(data->map->c);
	data->tex->cc_floor = rgb_to_int(data->map->f);
	if (!data->tex->cc_ceiling || !data->tex->cc_floor)
		return (ft_putstr_fd("Error: invalid textures convert.\n", 2), false);
	data->tex->textures = ft_calloc(5, sizeof(int *));
	if (!data->tex->textures)
		return (ft_putstr_fd("Error: invalid malloc.\n", 2), false);
	data->tex->textures[NORTH] = xpm_to_img(data, data->map->no);
	data->tex->textures[SOUTH] = xpm_to_img(data, data->map->so);
	data->tex->textures[EAST] = xpm_to_img(data, data->map->ea);
	data->tex->textures[WEST] = xpm_to_img(data, data->map->we);
	if (!data->tex->textures[NORTH] || !data->tex->textures[SOUTH]
		|| !data->tex->textures[EAST] || !data->tex->textures[WEST])
		return (false);
	return (true);
}

bool	init_tex_pixels(t_data *data)
{
	int	i;

	if (data->tex->texture_pixels)
		free_int_array(data->tex->texture_pixels);
	data->tex->texture_pixels = ft_calloc(data->win_height + 1, \
		sizeof * data->tex->texture_pixels);
	if (!data->tex->texture_pixels)
		return (ft_putstr_fd("Error: invalid malloc.\n", 2), false);
	i = 0;
	while (i < data->win_height)
	{
		data->tex->texture_pixels[i] = ft_calloc(data->win_width + 1,
				sizeof * data->tex->texture_pixels);
		if (!data->tex->texture_pixels[i])
			return (ft_putstr_fd("Error: invalid malloc.\n", 2), false);
		i++;
	}
	return (true);
}

static void	get_index(t_data *data, t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			data->tex->index = WEST;
		else
			data->tex->index = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			data->tex->index = SOUTH;
		else
			data->tex->index = NORTH;
	}
}

void	update_tex_pixels(t_data *data, t_raycast *ray, int x)
{
	int			y;
	int			color;

	get_index(data, ray);
	data->tex->x = (int)(ray->wall * data->tex->size);
	if ((!ray->side && ray->dir_x < 0) || (ray->side && ray->dir_y > 0))
		data->tex->x = data->tex->size - data->tex->x - 1;
	data->tex->step = 1.0 * data->tex->size / ray->line_height;
	data->tex->pos = (ray->draw_start - data->win_height / 2
			+ ray->line_height / 2) * data->tex->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		data->tex->y = (int)data->tex->pos & (data->tex->size - 1);
		data->tex->pos += data->tex->step;
		color = data->tex->textures[data->tex->index] \
			[data->tex->size * data->tex->y + data->tex->x];
		if (data->tex->index == NORTH || data->tex->index == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0)
			data->tex->texture_pixels[y][x] = color;
		y++;
	}
}
