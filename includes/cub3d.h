/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:06:46 by digoncal          #+#    #+#             */
/*   Updated: 2024/04/04 17:07:39 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ---------- LIBRARIES ---------- */

# include "libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>

/*---------- MACROS ----------*/

# define S_W 1900 //screen width
# define S_H 1000 //screen height
# define TILE_SIZE 30
# define FOV 60 //field of view
# define ROT_SPEED 0.05 //rotation speed
# define PLAYER_SPEED 2
# define S_ROTATION 5

/*------------- Structures ---------------*/

typedef enum e_rotation
{
	RIGHT,
	LEFT,
}	t_rotation;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_player
{
	t_pos	pos;
	double	angle;
	float	fov;
	int		rot;
	int		left;
	int		right;
	int		front;
	int		back;
	//t_pos	next_pos;
}	t_player;

typedef struct s_raycast
{
	double	ray_angle;
	double	distance; //distance to the wall
	int		wall; //flag for wall
}		t_raycast;

typedef struct s_map
{
	char	**layout;
	int		map_width;
	int		map_height;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
}	t_map;

typedef struct s_img
{
	void	*mlx_img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	t_raycast	*ray;
	t_map		*map;
	t_player	*player;
	void		*mlx;
	void		*win;
	t_img		img;
}	t_data;

/*---------- FUNCTIONS ----------*/

//init
t_data	*init_data(void);
void	init_img(t_data *data);
void	mlx_data_init(t_data *data);

//free
void	free_data(t_data *data);
void	free_array(char **arr);

//validate
bool	valid_file(char *file, char *ext, bool msg);
bool	valid_map(t_data *data, char *file);
bool	validate_identifiers(t_data *data);

//parser & utils
bool	parse_identifiers(t_data *data, char *file);
bool	parse_map(t_data *data, char *file);
bool	parse_player(t_data *data);
void	get_direction(t_data *data, char c);
char	**save_map(char **map, int fd);
int		map_lines(char *file);

//utils
char	*trim_content(char *str);
bool	is_digit(char *str);

//map utils
char	*copy_map_line(const char *src, int len);
bool	invalid_map(char **map);

//render
void	render(t_data *data);
int		handle_keys(int keysym, t_data *data);
int		ft_quit(t_data *data);

void    set_player(t_player *player);
#endif