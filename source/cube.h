/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 02:02:54 by jde-orma          #+#    #+#             */
/*   Updated: 2024/09/05 02:02:54 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# include "../libraries/libft/source/libft.h"
# include "../libraries/minilibx-linux/mlx.h"

/* Game window settings */
# define SCREENWIDTH 1280
# define SCREENHEIGTH 960
# define TEXTUREWIDTH 64
# define TEXTUREHEIGHT 64
# define CAMERAANGLE 0.66
# define GAMENAME "CUB3D"
# define DISTANCETOWALL 0.5
# define MOV_SPEED 0.05
# define ROTATIONSPEED 0.05

/* Array positions for the textures*/
# define SO 0
# define NO 1
# define EA 2
# define WE 3

/* Axis value for the raycasting functions */
#define X_AXIS 0
#define Y_AXIS 1

/* Linux qwerty key values */
#define UPARROW_KEY 65362
#define DOWNARROW_KEY 65364
#define RIGHTARROW_KEY 65363
#define LEFTARROW_KEY 65361
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100
#define Q_KEY 113
#define ESC_KEY 65307

/* defines for the movement management */
#define ENABLE_MOVE 1
#define DISABLE_MOVE 0

/* Boolean (tipe int )*/
#define FALSE 0
#define TRUE 1

/* Movement function modes defines */
#define RIGHT -1
#define LEFT 1
#define FORWARD 1
#define BACKWARD -1

/* Free functions modes */
#define FREE_TEXTURES 0
#define FREE_ALL 1

typedef struct s_map
{
	char		**map;
	int			**imap;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			map_size[2];
	int			player_position[2];
	int			player_direction[2];
	int			f;
	int			c;
	int			start_map;
}				t_map;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}			t_img;

typedef struct s_move
{
	int	forward;
	int	bakcward;
	int	rotate_right;
	int	rotate_left;
}	t_move;

typedef struct s_ray
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	int		stepx;
	int		stepy;
	double	perpwalldist;
	int		hit;
	int		side;
}			t_ray;

typedef struct s_pos_dir
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}			t_pos_dir;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_w;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_pos_dir	pos_dir;
	int			screenwidth;
	int			screenheigth;
	int			**textures;
	t_map		info;
	t_img		img_pp;
	t_img		texture[4];
	t_move		move;
}				t_data;

typedef struct s_draw
{
	int		drawstart;
	int		drawend;
	int		texnum;
	int		texx;
	double	wallx;
	int		lineheight;
}			t_draw;

/* Utils */
int		ft_close(void *param);
void	ft_free_cub(char *str, t_map *cub, int mode);

/* Raycasting */
t_ray	ft_init_ray(t_data dt, int x);
void	ft_init_side(t_data dt, t_ray *ray);
int		ft_raycasting(void *param);
void	ft_raycasting_dda_algorithm(t_ray *ray, int **map);
int		ft_move(t_data *dt);
void	ft_get_draw_info(t_data dt, t_ray ray, t_draw *draw);
void	ft_mlx_put_line(t_data *data, int x, t_draw draw);

/* Textures */
void	ft_free_textures(int **textures);
t_img	ft_read_texture(void *mlx, char *name, t_data *dt);

/* Game */
void	ft_game(t_map info);
int		ft_press_key(int key, void *param);
int		ft_release_key(int key, void *param);
void	ft_move_rotate(t_data *dt, double rotspeed, int sign);
void	ft_move_forward_backward(t_data *dt, double movespeed, int sign);

#endif
