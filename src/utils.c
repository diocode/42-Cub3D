/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:45:34 by digoncal          #+#    #+#             */
/*   Updated: 2024/03/27 16:45:34 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


static int	map_lines(char *file)
{
	char	*gnl;
	int		lines;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	lines = 0;
	gnl = get_next_line(fd);
	while (gnl && lines++ >= 0)
	{
		free(gnl);
		gnl = get_next_line(fd);
	}
	free(gnl);
	close(fd);
	return (lines);
}

char	**file_to_map(char *file)
{
	int		lines;
	int		fd;
	int		i;
	char	**map;

	lines = map_lines(file);
	map = ft_calloc(lines + 1, sizeof(char *));
	if (!map)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = -1;
	while (++i < lines)
	{
		map[i] = get_next_line(fd);
		if (!map[i] || map[i][0] == '\r')
		{
			free_array(map);
			close(fd);
			return (NULL);
		}
	}
	close(fd);
	return (map);
}

bool	is_digit(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
	}
	return (true);
}