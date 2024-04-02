/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:54:41 by digoncal          #+#    #+#             */
/*   Updated: 2024/03/25 13:54:41 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	validate_rgb(char *str)
{
	char	**rgb;
	int		i;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_array(rgb);
		return (false);
	}
	i = -1;
	while (rgb[++i])
	{
		if (!is_digit(rgb[i]) || ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255
			|| ft_strlen(rgb[i]) > 3)
		{
			free_array(rgb);
			return (false);
		}
	}
	free_array(rgb);
	return (true);
}

bool	validate_identifiers(t_data *data)
{
	if (!(data->map->no && data->map->so && data->map->we && data->map->ea
			&& data->map->f && data->map->c))
		return (false);
	if (!((valid_file(data->map->no, ".xpm", false)
				|| valid_file(data->map->no, ".png", false))
			&& (valid_file(data->map->so, ".xpm", false)
				|| valid_file(data->map->so, ".png", false))
			&& (valid_file(data->map->we, ".xpm", false)
				|| valid_file(data->map->we, ".png", false))
			&& (valid_file(data->map->ea, ".xpm", false)
				|| valid_file(data->map->ea, ".png", false))))
		return (false);
	if (!validate_rgb(data->map->f) || !validate_rgb(data->map->c))
		return (false);
	return (true);
}

bool	valid_map(t_data *data, char *file)
{
	if (!parse_identifiers(data, file))
		return (false);
	if (!parse_map(data, file))
		return (false);
	if (!parse_player(data))
		return (false);
	return (true);
}

bool	valid_file(char *file, char *ext, bool msg)
{
	char	*tmp_file;
	int		fd;

	tmp_file = ft_strrchr(file, '.');
	if (ft_strcmp(tmp_file, ext))
	{
		if (msg)
		{
			ft_putstr_fd("Error: ", 2);
			ft_putstr_fd(file, 2);
			ft_putstr_fd(" is not a valid extension.\n", 2);
		}
		return (false);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (msg)
			ft_putstr_fd("Error: can't open the file.\n", 2);
		return (false);
	}
	close(fd);
	return (true);
}
