/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:22:29 by digoncal          #+#    #+#             */
/*   Updated: 2024/03/22 16:22:29 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static	void	dev_mod(t_data *data)
{
	int i = 0;
	printf("NO-> \"%s\"\nSO-> \"%s\"\nWE-> \"%s\"\nEA-> \"%s\"\nF-> \"%s\"\nC-> \"%s\"\n\n", data->map->no, data->map->so, data->map->we, data->map->ea, data->map->f, data->map->c);
	while (data->map->layout[i] != NULL) {
		printf("%s", data->map->layout[i]);
		i++;
	}
	printf("\n");
}
int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (ft_putstr_fd("Error: no file provided.\n", 2), 1);
	if (!valid_file(av[1], ".cub", true))
		return (1);
	data = init_data();
	if (!data || !valid_map(data, av[1]))
		return (free_data(data), 1);
	dev_mod(data);
	free_data(data);
}
