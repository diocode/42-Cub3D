/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:06:52 by digoncal          #+#    #+#             */
/*   Updated: 2024/07/17 13:04:38 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	valid_border(char **map)
{
	int	y;
	int	lines;

	lines = 0;
	while (map[lines])
		lines++;
	if (ft_strchr(map[0], 'F') || ft_strchr(map[lines - 1], 'F'))
		return (false);
	y = -1;
	while (map[++y])
		if (map[y][0] == 'F' || map[y][ft_strlen(map[y]) - 1] == 'F')
			return (false);
	return (true);
}

static void	fill(char **map, int y, int x)
{
	if (x < 0 || y < 0 || !map[y] || map[y][x] == '\0')
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	fill(map, y - 1, x);
	fill(map, y + 1, x);
	fill(map, y, x - 1);
	fill(map, y, x + 1);
}

static	char	**copy_darr(char **arr)
{
	char	**copy;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	copy = ft_calloc(i + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		copy[i] = ft_strdup(arr[i]);
		if (!copy[i])
			return (free_array(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	*find_zero(char **map_copy, int *pos)
{
	int	y;
	int	x;

	y = -1;
	while (map_copy[++y])
	{
		x = 0;
		while (map_copy[y][x] == ' ' || map_copy[y][x] == '1')
			x++;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == '0')
			{
				pos[0] = y;
				pos[1] = x;
				return (pos);
			}
			x++;
		}
	}
	pos[0] = -1;
	pos[1] = -1;
	return (pos);
}

bool	border_check(char **map)
{
	char	**map_copy;
	int		*pos;

	map_copy = copy_darr(map);
	if (!map_copy)
		return (true);
	pos = malloc(sizeof(int) * 2);
	if (!pos)
		return (true);
	pos = find_zero(map_copy, pos);
	while (pos[0] != -1 && pos[1] != -1)
	{
		fill(map_copy, pos[0], pos[1]);
		pos = find_zero(map_copy, pos);
	}
	free(pos);
	if (!valid_border(map_copy))
	{
		free_array(map_copy);
		return (ft_putstr_fd("Error: invalid map borders.\n", 2), true);
	}
	free_array(map_copy);
	return (false);
}
