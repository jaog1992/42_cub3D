/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:53:26 by jde-orma          #+#    #+#             */
/*   Updated: 2024/09/05 00:53:26 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_free_textures(int **textures)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(textures[i]);
		i++;
	}
	free(textures);
}

t_img	ft_read_texture(void *mlx, char *name, t_data *data)
{
	t_img	image;

	image.img = mlx_xpm_file_to_image(mlx, name, &image.x, &image.y);
	if (!image.img)
		ft_free_cub("Error\nWrong XPM\n", &data->info, FREE_ALL);
	image.addr = (int *) mlx_get_data_addr(image.img, &image.bits_per_pixel,
			&image.line_length, &image.endian);
	image.line_length = image.line_length / 4;
	return (image);
}
