/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:38:19 by digoncal          #+#    #+#             */
/*   Updated: 2024/04/02 15:38:19 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_direction(t_data *data, char c)
{
	if (c == 'N')
		data->player->front = 1;
	else if (c == 'S')
		data->player->back = 1;
	else if (c == 'W')
		data->player->left = 1;
	else if (c == 'E')
		data->player->right = 1;
}

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

int	map_lines(char *file)
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

char	**save_map(char **map, int fd)
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
			map[i++] = copy_map_line(gnl, ft_strlen(gnl) - 1);
		free(gnl);
		gnl = get_next_line(fd);
	}
	free(gnl);
	return (map);
}
