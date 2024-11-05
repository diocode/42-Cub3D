/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:07:27 by digoncal          #+#    #+#             */
/*   Updated: 2024/11/05 15:20:03 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	init_texture_img(t_data *data, t_img *image, char *path)
{
	int	size;

	size = TEX_SIZE;
	image->addr = NULL;
	image->bpp = 0;
	image->line_len = 0;
	image->endian = 0;
	image->mlx_img = mlx_xpm_file_to_image(data->mlx, path, &size, &size);
	if (!image->mlx_img)
		return (ft_putstr_fd("Error\nminilibx failed.\n", 2), true);
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
	buffer = ft_calloc(1, sizeof * buffer * TEX_SIZE * TEX_SIZE);
	if (!buffer)
		return (ft_putstr_fd("Error\ninvalid malloc.\n", 2), NULL);
	y = 0;
	while (y < TEX_SIZE)
	{
		x = 0;
		while (x < TEX_SIZE)
		{
			buffer[y * TEX_SIZE + x] = tmp.addr[y * TEX_SIZE + x];
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
		return (ft_putstr_fd("Error\ntextures not found.\n", 2), false);
	data->tex->textures = ft_calloc(5, sizeof(int *));
	if (!data->tex->textures)
		return (ft_putstr_fd("Error\ninvalid malloc.\n", 2), false);
	data->tex->textures[NORTH] = xpm_to_img(data, data->map_info->no);
	data->tex->textures[SOUTH] = xpm_to_img(data, data->map_info->so);
	data->tex->textures[EAST] = xpm_to_img(data, data->map_info->ea);
	data->tex->textures[WEST] = xpm_to_img(data, data->map_info->we);
	if (!data->tex->textures[NORTH] || !data->tex->textures[SOUTH]
		|| !data->tex->textures[EAST] || !data->tex->textures[WEST])
		return (false);
	return (true);
}

static void	pick_texture(t_data *data, t_raycast *ray)
{
	if (!ray->side)
	{
		if (ray->dir.x < 0)
			data->tex->index = WEST;
		else
			data->tex->index = EAST;
	}
	else
	{
		if (ray->dir.y > 0)
			data->tex->index = SOUTH;
		else
			data->tex->index = NORTH;
	}
}

void	update_tex_pixels(t_data *data, t_raycast *ray, int x)
{
	int	y;
	int	color;

	pick_texture(data, ray);
	data->tex->x = (int)(ray->wall_tex * TEX_SIZE);
	if ((ray->side == 0 && ray->dir.x < 0)
		|| (ray->side == 1 && ray->dir.y > 0))
		data->tex->x = TEX_SIZE - data->tex->x - 1;
	data->tex->step = 1.0 * TEX_SIZE / ray->line_height;
	data->tex->pos = (ray->draw_start - WIN_HEIGHT / 2 \
				+ (double)ray->line_height / 2) * data->tex->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		data->tex->y = (int)data->tex->pos & (TEX_SIZE - 1);
		data->tex->pos += data->tex->step;
		color = data->tex->textures[data->tex->index] \
				[TEX_SIZE * data->tex->y + data->tex->x];
		if (data->tex->index == NORTH || data->tex->index == EAST)
			color = (color >> 1) & 0x7F7F7F;
		if (color > 0)
			data->tex->texture_pixels[y][x] = color;
		y++;
	}
}
