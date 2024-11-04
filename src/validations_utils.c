/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:12:52 by digoncal          #+#    #+#             */
/*   Updated: 2024/07/01 16:37:59 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	lines_result(char *gnl, int fd, int lines, bool flg)
{
	free(gnl);
	close(fd);
	if (flg)
		return (0);
	return (lines);
}

bool	only_spaces(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ' && str[i] != '\n')
			return (false);
	}
	return (true);
}

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
