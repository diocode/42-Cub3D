/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:14:24 by digoncal          #+#    #+#             */
/*   Updated: 2024/07/18 18:52:56 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_textures(t_textures *tex)
{
	if (tex->texture_pixels)
		free_int_array(tex->texture_pixels);
	if (tex->textures)
		free_int_array(tex->textures);
	free(tex);
}

void	init_textures(t_data *data)
{
	data->tex->index = 0;
	data->tex->texture_pixels = NULL;
	data->tex->textures = NULL;
	data->tex->step = 0;
	data->tex->pos = 0;
	data->tex->x = 0;
	data->tex->y = 0;
}

bool	init_tex_pixels(t_data *data)
{
	int	i;

	if (data->tex->texture_pixels)
		free_int_array(data->tex->texture_pixels);
	data->tex->texture_pixels = ft_calloc(WIN_HEIGHT + 1, \
		sizeof * data->tex->texture_pixels);
	if (!data->tex->texture_pixels)
		return (ft_putstr_fd("Error: invalid malloc.\n", 2), false);
	i = 0;
	while (i < WIN_HEIGHT)
	{
		data->tex->texture_pixels[i] = ft_calloc(WIN_WIDTH + 1,
				sizeof * data->tex->texture_pixels);
		if (!data->tex->texture_pixels[i])
			return (ft_putstr_fd("Error: invalid malloc.\n", 2), false);
		i++;
	}
	return (true);
}
