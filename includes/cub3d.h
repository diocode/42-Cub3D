/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:06:46 by digoncal          #+#    #+#             */
/*   Updated: 2024/04/12 14:14:13 by gabrrodr         ###   ########.fr       */
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

# define WIN_HEIGHT 640
# define WIN_WIDTH 640
# define ROT_SPEED 0.015 //rotation speed
# define PLAYER_SPEED 0.0125
# define TEXTURE_SIZE 64

/*------------- Structures ---------------*/

enum e_texture
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

typedef enum e_rotation
{
	RIGHT,
	LEFT,
}	t_rotation;

typedef struct s_pos
{
	int		x;
	int		y;
}	t_pos;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	angle;
	t_pos 	move;
	int 	rotate;
	int 	moved;
}	t_player;

typedef struct s_raycast
{
	double	ray_angle;//camera
	double 	dir_x;
	double  dir_y;
	double	distance; //wall distance
	int		side; //flag for wall
	int		map_x;
	int		map_y;
	int 	line_height;
	int 	draw_start;
	int 	draw_end;
	double	wall;
	double	horiz_x;//side distance
	double	horiz_y;
	double	vert_x;//delta distance
	double	vert_y;
	int		step_x;
	int  	step_y;
}		t_raycast;

typedef struct s_textures
{
	int		**texture_pixels;
	int		**textures;
	int		cc_floor;
	int		cc_ceiling;
	int		size;
	int		index;
	double	step;
	double	pos;
	int		x;
	int		y;
}	t_textures;

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
	t_textures	*tex;
	t_player	*player;
	int			win_height;
	int			win_width;
	void		*mlx;
	void		*win;
	t_img		img;
}	t_data;

/*---------- FUNCTIONS ----------*/

//init
t_data			*init_data(void);
void			init_img(t_img *img);
void			mlx_data_init(t_data *data);
bool			init_mlx_img(t_data *data, t_img *image, int width, int height);
void			render_img(t_data *data);
void			raycast_init(t_raycast *raycast);

//free
void			free_data(t_data *data);
void			free_array(char **arr);
void			free_int_array(int **arr);

//validate
bool			valid_file(char *file, char *ext, bool msg);
bool			valid_map(t_data *data, char *file);
bool			validate_identifiers(t_data *data);

//parser & utils
bool			parse_identifiers(t_data *data, char *file);
bool			parse_map(t_data *data, char *file);
bool			parse_player(t_data *data);
void			get_direction(t_data *data, char c);
char			**save_map(char **map, int fd);
int				map_lines(char *file);

//utils
char			*trim_content(char *str);
bool			is_digit(char *str);
int				rgb_to_int(char *rgb);

//map utils
char			*copy_map_line(const char *src, int len);
bool			invalid_map(char **map);

//render
void			render(t_data *data);
void			render_img(t_data *data);
int     		handle_keys(int keysym, t_data *data);
int    			ft_quit(t_data *data);

//render_frame
void			render_frame(t_data *data);

//textures
bool			handle_textures(t_data *data);
bool			init_tex_pixels(t_data *data);
void			update_tex_pixels(t_data *data, t_raycast *ray, int x);

//movement
bool			move_player(t_data *data);

//input
void    		check_input(t_data *data);
int				keyrelease_handle(int keysym, t_data *data);
int				keypress_handle(int keysym, t_data *data);

void    		set_player(t_player *player);
int				print_frame(t_data *data);

#endif