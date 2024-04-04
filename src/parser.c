/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:50:00 by digoncal          #+#    #+#             */
/*   Updated: 2024/04/04 12:00:18 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	save_identifier(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		data->map->no = trim_content(line + i + 2);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		data->map->so = trim_content(line + i + 2);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		data->map->we = trim_content(line + i + 2);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		data->map->ea = trim_content(line + i + 2);
	else if (line[i] == 'F')
		data->map->f = trim_content(line + i + 1);
	else if (line[i] == 'C')
		data->map->c = trim_content(line + i + 1);
}

bool	parse_identifiers(t_data *data, char *file)
{
	char	*line;
	int		fd;

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

static char	**get_map(char *file)
{
	int		lines;
	int		fd;
	char	**map;

	lines = map_lines(file);
	if (!lines)
		return (NULL);
	map = ft_calloc(lines + 1, sizeof(char *));
	if (!map)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	save_map(map, fd);
	close(fd);
	return (map);
}

bool	parse_map(t_data *data, char *file)
{
	data->map->layout = get_map(file);
	if (!data->map->layout)
		return (ft_putstr_fd("Error: invalid map.\n", 2), false);
	if (invalid_map(data->map->layout))
		return (false);
	return (true);
}

bool	parse_player(t_data *data)
{
	int	i;
	int	j;

	if (!data->player)
		return (ft_putstr_fd("Error: invalid player.\n", 2), false);
	i = -1;
	while (data->map->layout[++i])
	{
		j = -1;
		while (data->map->layout[i][++j])
		{
			if (data->map->layout[i][j] == 'N' || data->map->layout[i][j] == 'S'
				|| data->map->layout[i][j] == 'W'
				|| data->map->layout[i][j] == 'E')
			{
				data->player->pos.x = j;
				data->player->pos.y = i;
				get_direction(data, data->map->layout[i][j]);
				return (true);
			}
		}
	}
	return (ft_putstr_fd("Error: invalid player.\n", 2), false);
}
