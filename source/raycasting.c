/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:52:55 by jde-orma          #+#    #+#             */
/*   Updated: 2024/09/05 00:52:55 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/* The sign of raydirx & raydiry determines the direction the ray traces.
deltadistx & deltadisty need to be positive for this calculus, thus the fabs */
void	ft_init_side(t_data data, t_ray *ray)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (data.pos_dir.posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - data.pos_dir.posx)
			* ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (data.pos_dir.posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - data.pos_dir.posy)
			* ray->deltadisty;
	}
}

/* Camerax = Calculates the ray position on the X axis on the camera using the
 screenwidth as reference raydirx and raydiry determine the ray position using
 the player position and camera vision angle as reference deltadistx and 
 deltadisty determine de increment of y or x for each cuadricule*/
t_ray	ft_init_ray(t_data data, int x)
{
	t_ray	ray;

	ray.hit = 0;
	ray.camerax = (2.0 * x / (double)data.screenwidth) - 1.0;
	ray.raydirx = data.pos_dir.dirx + (data.pos_dir.planex * ray.camerax);
	ray.raydiry = data.pos_dir.diry + (data.pos_dir.planey * ray.camerax);
	ray.mapx = (int)data.pos_dir.posx;
	ray.mapy = (int)data.pos_dir.posy;
	if (!ray.raydirx)
		ray.deltadistx = 1e30;
	else
		ray.deltadistx = fabs(1 / ray.raydirx);
	if (!ray.raydiry)
		ray.deltadisty = 1e30;
	else
		ray.deltadisty = fabs(1 / ray.raydiry);
	ft_init_side(data, &ray);
	return (ray);
}

/* The DDA (Digital differencital analizer) algorithm nucleus traces the ray
 untill it hits the wall (map[x][y] == 1).
 It traces the movement of the ray one square at a time.

 Bare in mind that deltax & deltay are constant for each and every square the
 ray crossess.

 The perpendicular distance from the camera to the wall is checked to solve 
 fish eye image distortion */
void	ft_raycasting_dda_algorithm(t_ray *ray, int **map)
{
	while (ray->hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = Y_AXIS;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = X_AXIS;
		}
		if (map[ray->mapx][ray->mapy] > 0)
			ray->hit = 1;
	}
	if (ray->side == Y_AXIS)
		ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
	else
		ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
}

/* It uses the ray info to know how to draw each pixel columns in the screen */
void	ft_get_draw_info(t_data data, t_ray ray, t_draw *draw)
{
	draw->lineheight = (int)(data.screenheigth / ray.perpwalldist);
	draw->drawstart = -draw->lineheight / 2 + data.screenheigth / 2;
	if (draw->drawstart < 0)
		draw->drawstart = 0;
	draw->drawend = draw->lineheight / 2 + data.screenheigth / 2;
	if (draw->drawend >= data.screenheigth)
		draw->drawend = data.screenheigth - 1;
	if (ray.side == Y_AXIS && ray.raydirx > 0)
		draw->texnum = NO;
	else if (ray.side == Y_AXIS && ray.raydirx < 0)
		draw->texnum = SO;
	else if (ray.side == X_AXIS && ray.raydiry > 0)
		draw->texnum = EA;
	else if (ray.side == X_AXIS && ray.raydiry < 0)
		draw->texnum = WE;
	if (ray.side == Y_AXIS)
		draw->wallx = data.pos_dir.posy + ray.perpwalldist * ray.raydiry;
	else
		draw->wallx = data.pos_dir.posx + ray.perpwalldist * ray.raydirx;
	draw->wallx -= floor((draw->wallx));
	draw->texx = (int)(draw->wallx * (double)TEXTUREWIDTH);
	if (ray.side == Y_AXIS && ray.raydirx > 0)
		draw->texx = TEXTUREWIDTH - draw->texx - 1;
	if (ray.side == X_AXIS && ray.raydiry < 0)
		draw->texx = TEXTUREWIDTH - draw->texx - 1;
}

/* It draws a ray for each of the pixels on the game screen */
int	ft_raycasting(void *param)
{
	int		i;
	t_ray	ray;
	t_draw	draw;
	t_data	*data;

	i = 0;
	data = (t_data *)param;
	ft_move(data);
	data->img_pp.img = mlx_new_image(data->mlx, SCREENWIDTH, SCREENHEIGTH);
	data->img_pp.addr = (int *) mlx_get_data_addr(data->img_pp.img,
			&data->img_pp.bits_per_pixel, &data->img_pp.line_length,
			&data->img_pp.endian);
	while (i < data->screenwidth)
	{
		ray = ft_init_ray(*data, i);
		ft_raycasting_dda_algorithm(&ray, data->info.imap);
		ft_get_draw_info(*data, ray, &draw);
		ft_mlx_put_line(data, i, draw);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_w, data->img_pp.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img_pp.img);
	return (EXIT_SUCCESS);
}
