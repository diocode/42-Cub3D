/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:22:29 by digoncal          #+#    #+#             */
/*   Updated: 2024/04/12 14:09:57 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_data		*data;

	if (ac != 2)
		return (ft_putstr_fd("Error: no file provided.\n", 2), 1);
	if (!valid_file(av[1], ".cub", true))
		return (1);
	data = init_data();
	if (!data || !valid_map(data, av[1]))
		return (free_data(data), 1);
	mlx_data_init(data);
	if (!handle_textures(data))
		return (1);
	render_img(data);
	check_input(data);
	mlx_loop_hook(data->mlx, print_frame, data);
    mlx_loop(data->mlx);
	free_data(data);
	return (0);
}
