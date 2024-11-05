/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:45:01 by digoncal          #+#    #+#             */
/*   Updated: 2024/11/05 15:20:08 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	valid_content(const char *line, int i)
{
	if (!((line[i] == 'N' && line[i + 1] == 'O')
			|| (line[i] == 'S' && line[i + 1] == 'O')
			|| (line[i] == 'W' && line[i + 1] == 'E')
			|| (line[i] == 'E' && line[i + 1] == 'A')
			|| line[i] == 'F' || line[i] == 'C'
			|| line[i] == '1' || line[i] == '\n'))
		return (false);
	return (true);
}

static bool	invalid_content(char *file)
{
	char	*line;
	int		fd;
	int		i;
	bool	flg;

	flg = false;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (!valid_content(line, i))
			flg = true;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (flg)
		return (ft_putstr_fd("Error\ninvalid map elements.\n", 2), true);
	return (false);
}

bool	valid_map(t_data *data, char *file)
{
	if (!parse_identifiers(data, file))
		return (false);
	if (!parse_map(data, file))
		return (false);
	if (!parse_player(data, data->map))
		return (false);
	if (invalid_content(file))
		return (false);
	return (true);
}

bool	valid_file(char *file, char *ext)
{
	char	*tmp_file;
	int		fd;

	tmp_file = ft_strrchr(file, '.');
	if (ft_strcmp(tmp_file, ext))
		return (false);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}
