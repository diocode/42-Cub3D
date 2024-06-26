/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:45:34 by digoncal          #+#    #+#             */
/*   Updated: 2024/04/03 12:22:44 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	rgb_to_int(char *str)
{
	int		res;
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (free_array(rgb), 0);
	res = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8 | ft_atoi(rgb[2]);
	free_array(rgb);
	return (res);
}

int	ft_quit(t_data *data)
{
	free_data(data);
	exit (1);
}

/* trim: spaces and new line */
char	*trim_content(char *str)
{
	int		i;
	int		j;
	char	*content;

	if (!str && !*str)
		return (NULL);
	i = 0;
	while (str[i] == ' ')
		i++;
	j = ft_strlen(str) - 1;
	while (str[j] == ' ')
		j--;
	if (str[j] == '\n')
		j--;
	content = ft_substr(str, i, j - i + 1);
	return (content);
}

bool	is_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
	}
	return (true);
}

char	*copy_map_line(const char *src, int len)
{
	int			i;
	char		*line;

	line = (char *) ft_calloc(len + 1, sizeof(char));
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
