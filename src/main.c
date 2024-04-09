/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:22:29 by digoncal          #+#    #+#             */
/*   Updated: 2024/04/04 11:58:49 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static	void	dev_mod(t_data *data)
{
	int i = 0;
	printf("\nNO-> \"%s\"\nSO-> \"%s\"\nWE-> \"%s\"\nEA-> \"%s\"\nF-> \"%s\"\nC-> \"%s\"\n\n", data->map->no, data->map->so, data->map->we, data->map->ea, data->map->f, data->map->c);
	printf("Map weight: %d\nMap height: %d\n\n", data->map->map_width, data->map->map_height);
	printf("Player: x-> %.2d | y-> %.2d | direction-> ", data->player->pos.x, data->player->pos.y);
	if (data->player->front)
		printf("Front(N)\n\n");
	else if (data->player->back)
		printf("Back(S)\n\n");
	else if (data->player->left)
		printf("Left(W)\n\n");
	else if (data->player->right)
		printf("Right(E)\n\n");
	printf("Ceiling color: %d\nFloor color: %d\n\n", data->tex->cc_ceiling, data->tex->cc_floor);
	while (data->map->layout[i] != NULL) {
		printf("%s", data->map->layout[i]);
		printf("\n");
		i++;
	}
	printf("\n");
}

int	main(int ac, char **av)
{
	t_data		*data;
	//t_raycast	*raycast;

	if (ac != 2)
		return (ft_putstr_fd("Error: no file provided.\n", 2), 1);
	if (!valid_file(av[1], ".cub", true))
		return (1);
	data = init_data();
	if (!data || !valid_map(data, av[1]))
		return (free_data(data), 1);
	init_img(data);
	dev_mod(data); //DEV MOD
	data->win = 0;
	render(data);
	free_data(data);
}
