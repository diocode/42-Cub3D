/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:26:12 by digoncal          #+#    #+#             */
/*   Updated: 2024/07/22 18:15:17 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (ft_putstr_fd("Error: no file provided\n", 2), 1);
	if (!valid_file(argv[1], ".cub"))
		return (ft_putstr_fd("Error: Invalid file\n", 2), 1);
	data = init_data();
	if (!data || !valid_map(data, argv[1]))
		return (free_data(data), 1);
	if (!handle_textures(data))
		return (1);
	render(data);
	move_player(data);
	init_game(data);
	free_data(data);
}
