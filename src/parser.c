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

static bool	check_start_end(char *str)
{
	int 	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '1')
		i++;
	if (i != 0 && (str[i] == '\0' || str[i] == '\n'))
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
		if (!start)
		{
			start = check_start_end(gnl);
			lines++;
		}
		else
			lines++;
		if (start && check_start_end(gnl) && lines > 1)
			break ;
		free(gnl);
		gnl = get_next_line(fd);
	}
	free(gnl);
	close(fd);
	return (lines);
}

static char	**get_map(char *file)
{
	int		lines;
//	int		fd;
//	int		i;
	char	**map;

	lines = map_lines(file);
	printf("lines: %d\n", lines);
	map = ft_calloc(lines + 1, sizeof(char *));
	if (!map)
		return (NULL);
	/*fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = -1;
	while (++i < lines)
	{
		map[i] = get_next_line(fd);
		if (!map[i] || map[i][0] == '\r')
		{
			free_array(map, lines);
			close(fd);
			return (NULL);
		}
	}
	close(fd);*/
	return (map);
}

bool	parse_map(t_data *data, char *file)
{
	data->map->layout = get_map(file);
	return (true);
	//return (ft_putstr_fd("Error: invalid map.\n", 2), false);
}
