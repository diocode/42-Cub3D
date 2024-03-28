/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:50:00 by digoncal          #+#    #+#             */
/*   Updated: 2024/03/27 17:16:46 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	save_identifier(t_data *data, char *line)
{
	int i;

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

static bool	check_start(const char *str)
{
	int 	i;
	bool	wall;

	wall = false;
	i = 0;
	while (str[i] == ' ' || str[i] == '1' || str[i] == '\n')
	{
		if (str[i] == '1')
			wall = true;
		i++;
	}
	if (i != 0 && str[i] == '\0' && wall)
		return (true);
	return (false);
}

static int	map_lines(char *file)
{
	char	*gnl;
	int		lines;
	int		fd;
	bool	start;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	start = false;
	lines = 0;
	gnl = get_next_line(fd);
	while (gnl)
	{
		if (check_start(gnl))
			start = true;
		if (start && gnl[0] != '\0' && gnl[0] != '\n')
			lines++;
		free(gnl);
		gnl = get_next_line(fd);
	}
	free(gnl);
	close(fd);
	return (lines);
}
static	char** save_map(char **map, int fd)
{
	char	*gnl;
	bool	start;
	int 	i;

	start = false;
	gnl = get_next_line(fd);
	i = 0;
	while (gnl)
	{
		if (check_start(gnl))
			start = true;
		if (start && gnl[0] != '\0' && gnl[0] != '\n')
			map[i++] = ft_strdup(gnl);
		free(gnl);
		gnl = get_next_line(fd);
	}
	free(gnl);
	return (map);
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
	return (true);
	//return (ft_putstr_fd("Error: invalid map.\n", 2), false);
}
