/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:50:00 by digoncal          #+#    #+#             */
/*   Updated: 2024/03/26 11:50:00 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	save_identifier(t_data *data, char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		data->map->no = ft_substr(line, 3, ft_strlen(line) - 4);
	else if (line[0] == 'S' && line[1] == 'O')
		data->map->so =ft_substr(line, 3, ft_strlen(line) - 4);
	else if (line[0] == 'W' && line[1] == 'E')
		data->map->we = ft_substr(line, 3, ft_strlen(line) - 4);
	else if (line[0] == 'E' && line[1] == 'A')
		data->map->ea = ft_substr(line, 3, ft_strlen(line) - 4);
	else if (line[0] == 'F')
		data->map->f = ft_substr(line, 2, ft_strlen(line) - 3);
	else if (line[0] == 'C')
		data->map->c = ft_substr(line, 2, ft_strlen(line) - 3);
}

bool	parse_identifiers(t_data *data, char *file)
{
	char 	*line;
	int 	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	line = get_next_line(fd);
	while (line)
	{
		save_identifier(data, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (validate_identifiers(data))
		return (true);
	return (ft_putstr_fd("Error: invalid identifiers.\n", 2), false);
}

static char *map_start(char *file)
{
	char *line;
	int fd;
	int i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '1')
			i++;
		free(line);
		if (line[i] == '\0')
			return (get_next_line(fd));
		line = get_next_line(fd);
	}
	close(fd);
	return (line);
}

bool	parse_map(t_data *data, char *file)
{
	data->map->layout = file_to_map(map_start(file));
	return (ft_putstr_fd("Error: invalid map.\n", 2), false);
}
