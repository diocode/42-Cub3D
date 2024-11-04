/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:54:17 by digoncal          #+#    #+#             */
/*   Updated: 2024/11/04 18:12:37 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_int_array(int **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	free_map_info(t_map_info *map_info)
{
	if (map_info->no)
		free(map_info->no);
	if (map_info->so)
		free(map_info->so);
	if (map_info->we)
		free(map_info->we);
	if (map_info->ea)
		free(map_info->ea);
	if (map_info->f)
		free(map_info->f);
	if (map_info->c)
		free(map_info->c);
	free(map_info);
}

int	ft_quit(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	mlx_mouse_show(data->mlx, data->win);
	if (data->img.mlx_img)
		mlx_destroy_image(data->mlx, data->img.mlx_img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->map)
		free_array(data->map);
	if (data->ray)
		free(data->ray);
	if (data->map_info)
		free_map_info(data->map_info);
	if (data->player)
		free(data->player);
	if (data->tex)
		free_textures(data->tex);
	free(data);
}
