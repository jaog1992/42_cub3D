/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:52:20 by jde-orma          #+#    #+#             */
/*   Updated: 2024/09/05 00:52:20 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_move_forward_backward(t_data *data, double movespeed, int sign)
{
	if (!data->info.imap[(int)(data->pos_dir.posx + sign * 
			data->pos_dir.dirx * movespeed)][(int)data->pos_dir.posy])
		data->pos_dir.posx += sign * data->pos_dir.dirx * movespeed;
	if (!data->info.imap[(int)data->pos_dir.posx]
			[(int)
			(data->pos_dir.posy + sign * data->pos_dir.diry * movespeed)])
		data->pos_dir.posy += sign * data->pos_dir.diry * movespeed;
}

void	ft_move_rotate(t_data *data, double rotspeed, int sign)
{
	double	tempdirx;
	double	tempplanex;

	tempdirx = data->pos_dir.dirx;
	tempplanex = data->pos_dir.planex;
	data->pos_dir.dirx = data->pos_dir.dirx * cos(sign * rotspeed)
		- data->pos_dir.diry * sin(sign * rotspeed);
	data->pos_dir.diry = tempdirx * sin(sign * rotspeed)
		+ data->pos_dir.diry * cos(sign * rotspeed);
	data->pos_dir.planex = data->pos_dir.planex * cos(sign * rotspeed)
		- data->pos_dir.planey * sin(sign * rotspeed);
	data->pos_dir.planey = tempplanex * sin(sign * rotspeed)
		+ data->pos_dir.planey * cos(sign * rotspeed);
}

int	ft_press_key(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == D_KEY || key == RIGHTARROW_KEY)
		data->move.rotate_right = ENABLE_MOVE;
	else if (key == A_KEY || key == LEFTARROW_KEY)
		data->move.rotate_left = ENABLE_MOVE;
	else if (key == S_KEY || key == DOWNARROW_KEY)
		data->move.bakcward = ENABLE_MOVE;
	else if (key == W_KEY || key == UPARROW_KEY)
		data->move.forward = ENABLE_MOVE;
	else if (key == Q_KEY || key == ESC_KEY)
		ft_close(param);
	return (EXIT_SUCCESS);
}

int	ft_release_key(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == D_KEY || key == RIGHTARROW_KEY)
		data->move.rotate_right = DISABLE_MOVE;
	else if (key == A_KEY || key == LEFTARROW_KEY)
		data->move.rotate_left = DISABLE_MOVE;
	else if (key == S_KEY || key == DOWNARROW_KEY)
		data->move.bakcward = DISABLE_MOVE;
	else if (key == W_KEY || key == UPARROW_KEY)
		data->move.forward = DISABLE_MOVE;
	return (EXIT_SUCCESS);
}

int	ft_move(t_data *data)
{
	double	movespeed;
	double	rotspeed;

	movespeed = MOV_SPEED;
	rotspeed = ROTATIONSPEED;
	if (data->move.rotate_right)
		ft_move_rotate(data, rotspeed, RIGHT);
	if (data->move.rotate_left)
		ft_move_rotate(data, rotspeed, LEFT);
	if (data->move.forward)
		ft_move_forward_backward(data, movespeed, FORWARD);
	if (data->move.bakcward)
		ft_move_forward_backward(data, movespeed, BACKWARD);
	return (EXIT_SUCCESS);
}
