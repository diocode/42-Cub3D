/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:22:29 by digoncal          #+#    #+#             */
/*   Updated: 2024/04/02 13:38:39 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_data		*data;
	t_player	*player;
	t_raycast	*raycast;

	if (ac != 2)
		return (ft_putstr_fd("Error: no file provided.\n", 2), 1);
	if (!valid_file(av[1], ".cub", true))
		return (1);
	data = init_data();
	if (!data || !valid_map(data, av[1]))
		return (free_data(data), 1);
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, \
	0, 0);
	//data->win = 0;
	//init_img(data);
	mlx_loop(data->mlx);
	printf("NO|%s\nSO|%s\nWE|%s\nEA|%s\nF|%s\nC|%s\n", data->map->no, data->map->so, data->map->we, data->map->ea, data->map->f, data->map->c);
	free_data(data);
}
