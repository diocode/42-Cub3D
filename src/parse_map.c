/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:45:24 by digoncal          #+#    #+#             */
/*   Updated: 2024/07/08 15:22:27 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	check_start(const char *str)
{
	int		i;
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

static char	*copy_map_line(const char *src, int len)
{
	int			i;
	char		*line;

	line = (char *)ft_calloc(len + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (src && src[i] && i < len)
	{
		line[i] = src[i];
		i++;
	}
	return (line);
}

static void	save_map(t_data *data, int fd)
{
	char	*gnl;
	bool	start;
	int		i;

	start = false;
	gnl = get_next_line(fd);
	i = 0;
	while (gnl)
	{
		if (check_start(gnl))
			start = true;
		if (start && gnl[0] != '\0' && gnl[0] != '\n')
			data->map[i++] = copy_map_line(gnl, ft_strlen(gnl) - 1);
		free(gnl);
		gnl = get_next_line(fd);
	}
	free(gnl);
}

static int	map_lines(char *file)
{
	char	*gnl;
	int		lines;
	int		fd;
	bool	start;
	bool	flg;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	flg = false;
	start = false;
	lines = 0;
	gnl = get_next_line(fd);
	while (gnl)
	{
		if (check_start(gnl))
			start = true;
		if (start && gnl[0] != '\0' && gnl[0] != '\n')
			lines++;
		if (start && (gnl[0] == '\0' || gnl[0] == '\n' || only_spaces(gnl)))
			flg = true;
		free(gnl);
		gnl = get_next_line(fd);
	}
	return (lines_result(gnl, fd, lines, flg));
}

bool	parse_map(t_data *data, char *file)
{
	int		lines;
	int		fd;

	lines = map_lines(file);
	if (lines < 3)
		return (ft_putstr_fd("Error: invalid map.\n", 2), false);
	data->map = ft_calloc(lines + 1, sizeof(char *));
	if (!data->map)
		return (ft_putstr_fd("Error: invalid memory allocation.\n", 2), false);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error: invalid file.\n", 2), false);
	save_map(data, fd);
	close(fd);
	if (border_check(data->map) || invalid_map(data->map))
		return (false);
	return (true);
}
