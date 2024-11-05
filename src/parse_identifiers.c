/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:05:51 by digoncal          #+#    #+#             */
/*   Updated: 2024/11/05 15:19:28 by gabrrodr         ###   ########.fr       */
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

static bool	validate_identifiers(t_data *data)
{
	if (!(data->map_info->no && data->map_info->so && data->map_info->we
			&& data->map_info->ea && data->map_info->f && data->map_info->c))
		return (false);
	if (!(valid_file(data->map_info->no, ".xpm")
			&& valid_file(data->map_info->so, ".xpm")
			&& valid_file(data->map_info->we, ".xpm")
			&& valid_file(data->map_info->ea, ".xpm")))
		return (false);
	if (!validate_rgb(data->map_info->f) || !validate_rgb(data->map_info->c))
		return (false);
	return (true);
}

static int	get_path(char **ptr, char *line, int i, int cut)
{
	if (*ptr && *ptr[0] != '\0')
		return (1);
	*ptr = trim_content(line + i + cut);
	return (0);
}

static int	save_identifier(t_data *data, char *line)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		status = get_path(&data->map_info->no, line, i, 2);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		status = get_path(&data->map_info->so, line, i, 2);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		status = get_path(&data->map_info->we, line, i, 2);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		status = get_path(&data->map_info->ea, line, i, 2);
	else if (line[i] == 'F')
		status = get_path(&data->map_info->f, line, i, 1);
	else if (line[i] == 'C')
		status = get_path(&data->map_info->c, line, i, 1);
	return (status);
}

bool	parse_identifiers(t_data *data, char *file)
{
	char	*line;
	int		fd;
	bool	error;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	error = false;
	line = get_next_line(fd);
	while (line)
	{
		if (save_identifier(data, line))
			error = true;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!error && validate_identifiers(data))
	{
		data->map_info->cc_ceiling = rgb_to_int(data->map_info->c);
		data->map_info->cc_floor = rgb_to_int(data->map_info->f);
		return (true);
	}
	return (ft_putstr_fd("Error\ninvalid identifiers.\n", 2), false);
}
