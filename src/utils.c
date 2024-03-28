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

/* trim: spaces and new line */
char *trim_content(char *str)
{
	int i;
	int j;
	char *content;

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
	int i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
	}
	return (true);
}