/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/0 00:50:25 by jde-orma          #+#    #+#             */
/*   Updated: 2024/09/0 00:50:25 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_mlx_put_pixel(t_data *data, int x, int y, int color)
{
	int	*dst;

	dst = data->img_pp.addr + (y * data->img_pp.line_length
			/ (data->img_pp.bits_per_pixel / 8) + x);
	*(unsigned int *)dst = color;
}

void	ft_mlx_put_line(t_data *data, int x, t_draw draw)
{
	int			y;
	int			texy;
	int			color;
	double		step;
	double		texpos;

	y = 0;
	step = 1.0 * TEXTUREHEIGHT / draw.lineheight;
	texpos = (draw.drawstart - data->screenheigth / 2 + draw.lineheight / 2)
		 * step;
	while (y < SCREENHEIGTH)
	{
		if (y < draw.drawstart)
			color = data->info.c;
		else if (y >= draw.drawend)
			color = data->info.f;
		else
		{
			texy = (int)texpos & (TEXTUREHEIGHT - 1);
			texpos += step;
			color = data->texture[draw.texnum].addr[TEXTUREHEIGHT * texy
				+ draw.texx];
		}
		ft_mlx_put_pixel(data, x, y, color);
		y++;
	}
}
