/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:06:46 by digoncal          #+#    #+#             */
/*   Updated: 2024/11/05 03:17:31 by digoncal         ###   ########.fr       */
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

# define WIN_HEIGHT 800
# define WIN_WIDTH 1000
# define TEX_SIZE 64
# define PLAYER_SPEED 0.05
# define ROT_SPEED 0.0045
# define DIST_EDGE_MOUSE_WRAP 50

/*------------- STRUCTURES ---------------*/

enum e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

typedef struct s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct s_img
{
	void	*mlx_img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_textures
{
	int		index;
	int		**texture_pixels;
	int		**textures;
	double	step;
	double	pos;
	int		x;
	int		y;
}				t_textures;

typedef struct raycast
{
	t_pos	dir;
	t_pos	next_dist; //distance to next x or y-side
	t_pos	grid_dist; //length of ray from one x or y-side to next x or y-side
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		draw_start;
	int		draw_end;
	bool	hit;
	bool	side;
	double	wall_dist;
	double	wall_tex;
	int		line_height;
}			t_raycast;

typedef struct s_player
{
	t_pos	position;
	t_pos	dir;
	t_pos	cam;
	int		moved;
	int		move_x;
	int		move_y;
	int		rotate;
}				t_player;

typedef struct s_map_info
{
	char	*so;
	char	*no;
	char	*ea;
	char	*we;
	char	*f;
	char	*c;
	int		cc_ceiling;
	int		cc_floor;
}			t_map_info;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	char		**map;
	t_raycast	*ray;
	t_map_info	*map_info;
	t_img		img;
	t_player	*player;
	t_textures	*tex;
}				t_data;

/*---------- FUNCTIONS ----------*/

//VALID MAP
bool	valid_file(char *file, char *ext);
bool	valid_map(t_data *data, char *file);
bool	parse_identifiers(t_data *data, char *file);
bool	is_digit(char *str);
char	*trim_content(char *str);
int		rgb_to_int(char *str);
bool	parse_map(t_data *data, char *file);
bool	invalid_map(char **map);
bool	only_spaces(const char *str);
bool	parse_player(t_data *data, char **map);
int		lines_result(char *gnl, int fd, int lines, bool flg);
bool	border_check(char **map);

//INIT & FREE
t_data	*init_data(void);
void	free_data(t_data *data);
void	free_array(char **arr);
int		ft_quit(t_data *data);
void	init_game(t_data *data);
void	init_mlx(t_data *data);
bool	init_mlx_img(t_data *data, t_img *img, int width, int height);
void	free_int_array(int **arr);

//RENDER GAME
void	raycast(t_data *data);
int		render_game(t_data *data);
void	render(t_data *data);

//MOVEMNET
int		handle_key_press(int keysym, t_data *data);
int		handle_key_release(int keysym, t_data *data);
int		move_player(t_data *data);
int		rotate_player(t_data *data, double dir, int dist);
int		mouse_handle(int x, int y, t_data *data);
bool	valid_move(t_data *data, double x, double y);
int		move_up(t_data *data);
int		move_down(t_data *data);
int		move_right(t_data *data);
int		move_left(t_data *data);

//TEXTURES
void	init_textures(t_data *data);
void	free_textures(t_textures *tex);
bool	init_tex_pixels(t_data *data);
bool	handle_textures(t_data *data);
void	update_tex_pixels(t_data *data, t_raycast *ray, int x);

#endif
