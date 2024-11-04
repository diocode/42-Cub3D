/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:25:27 by digoncal          #+#    #+#             */
/*   Updated: 2024/07/15 12:40:33 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	invalid_walls(char **map, int i, int j)
{
	if (i > 1 && ft_strlen(map[i]) > ft_strlen(map[i - 1])
		&& j >= ft_strlen(map[i - 1]) && map[i][j] && map[i][j] != '1')
		return (true);
	if (map[i + 1] != NULL && ft_strlen(map[i]) > ft_strlen(map[i + 1])
		&& j >= ft_strlen(map[i + 1]) && map[i][j] && map[i][j] != '1')
		return (true);
	if (i == 0 || map[i + 1] == NULL)
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (true);
	return (false);
}

static bool	invalid_borders(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strlen(line) > 1)
		if (line[i] != '1')
			return (true);
	j = ft_strlen(line) - 1;
	while (line[j] == ' ')
		j--;
	if (line[j] != '1')
		return (true);
	if (ft_strlen(line) == 1 && line[i] != '1')
		return (true);
	return (false);
}

static bool	invalid_map_elements(char const *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ' && str[i] != '1' && str[i] != '0'
			&& str[i] != 'N' && str[i] != 'S' && str[i] != 'W' && str[i] != 'E')
		{
			printf("str[i] = %c\n", str[i]);
			return (ft_putstr_fd("Error: invalid map elements.\n", 2), true);
		}
	}
	return (false);
}

static bool	invalid_spaces(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				if (map[i][j - 1] != '1' && map[i][j - 1] != ' '
					&& map[i][j + 1] != '1' && map[i][j + 1] != ' '
					&& map[i - 1] && map[i - 1][j] != '1'
					&& map[i - 1][j] != ' '
					&& map[i + 1] && map[i + 1][j] != '1'
					&& map[i + 1][j] != ' ')
					return (ft_putstr_fd("Error: invalid map "
							"borders.\n", 2), true);
			j++;
		}
	}
	return (false);
}

bool	invalid_map(char **map)
{
	int	i;
	int	j;

	if (invalid_spaces(map))
		return (true);
	i = -1;
	while (map[++i])
	{
		if (invalid_map_elements(map[i]))
			return (true);
		j = 0;
		while (map[i][j])
		{
			while (map[i][j] == ' ')
				j++;
			if (!map[i][j])
				break ;
			if (invalid_borders(map[i]))
				return (ft_putstr_fd("Error: invalid map borders.\n", 2), true);
			if (invalid_walls(map, i, j))
				return (ft_putstr_fd("Error: invalid map walls.\n", 2), true);
			j++;
		}
	}
	return (false);
}
