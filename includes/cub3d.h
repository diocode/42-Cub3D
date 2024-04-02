/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:06:46 by digoncal          #+#    #+#             */
/*   Updated: 2024/04/02 13:29:35 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ---------- LIBRARIES ---------- */

# include "libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <stdbool.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>

/*---------- MACROS ----------*/


/*------------- Structures ---------------*/

typedef struct s_pos
{
	double	x;
	double	y;
} t_pos;

typedef struct	s_raycast
{
	
}	t_raycast;

typedef struct s_player
{
	t_pos	map_pos;
	double	speed;
	double	angle;
	int	front;
	int	back;
	int	left;
	int	right;
	int	exit;
}	t_player;

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
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
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

#endif