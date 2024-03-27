/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:06:46 by digoncal          #+#    #+#             */
/*   Updated: 2024/03/22 16:06:46 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ---------- LIBRARIES ---------- */

# include "libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <stdbool.h>
# include <fcntl.h>

/*---------- MACROS ----------*/


/*------------- Structures ---------------*/

typedef struct s_map
{
	char 	**layout;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char 	*f;
	char 	*c;
}	t_map;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	t_map	*map;
	void	*mlx;
	void	*win;
	t_img	img;
}	t_data;


/*---------- FUNCTIONS ----------*/

//init
t_data	*init_data(void);

//free
void	free_data(t_data *data);
void	free_array(char **arr);

//validate
bool	valid_file(char *file, char *ext, bool msg);
bool	valid_map(t_data *data, char *file);
bool	validate_identifiers(t_data *data);

//parser
bool	parse_identifiers(t_data *data, char *file);
bool	parse_map(t_data *data, char *file);

//utils
bool	is_digit(char *str);
char	**file_to_map(char *file);

#endif