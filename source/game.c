/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:51:05 by jde-orma          #+#    #+#             */
/*   Updated: 2024/09/05 00:51:05 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_free_cub(char *str, t_map *map, int mode)
{
	int	i;

	i = 0;
	printf("%s", str);
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
	if (mode == FREE_ALL)
	{
		ft_free2dstr(map->map);
		while (i < map->map_size[0])
			free(map->imap[i++]);
		free(map->imap);
	}
	exit(EXIT_SUCCESS);
}

/* Function responsible of seamlessly exiting cub3D when the user closes or exits the window*/
int	ft_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_destroy_window(data->mlx, data->mlx_w);
	ft_free_cub("Game exited\n", &data->info, FREE_ALL);
	exit(EXIT_SUCCESS);
}

/* intialises the data structure*/
void	ft_init_data(t_data *data, t_map info)
{
	data->info = info;
	data->mlx = mlx_init();
	data->screenwidth = SCREENWIDTH;
	data->screenheigth = SCREENHEIGTH;
	data->move.forward = DISABLE_MOVE;
	data->move.bakcward = DISABLE_MOVE;
	data->move.rotate_right = DISABLE_MOVE;
	data->move.rotate_left = DISABLE_MOVE;
	data->texture[SO] = ft_read_texture(data->mlx, data->info.so, data);
	data->texture[NO] = ft_read_texture(data->mlx, data->info.no, data);
	data->texture[EA] = ft_read_texture(data->mlx, data->info.ea, data);
	data->texture[WE] = ft_read_texture(data->mlx, data->info.we, data);
	data->pos_dir.posx = (double)info.player_position[Y_AXIS] + DISTANCETOWALL;
	data->pos_dir.posy = (double)info.player_position[X_AXIS] + DISTANCETOWALL;
	data->pos_dir.dirx = (double)info.player_direction[Y_AXIS];
	data->pos_dir.diry = (double)info.player_direction[X_AXIS];
	data->pos_dir.planex = data->pos_dir.diry * (CAMERAANGLE);
	data->pos_dir.planey = data->pos_dir.dirx * (-CAMERAANGLE);
	data->mlx_w = mlx_new_window(data->mlx, SCREENWIDTH, SCREENHEIGTH, GAMENAME);
}

/* main "loop" of the cub3d. The raycasting function is called here */
void	ft_game(t_map info)
{
	t_data	data;

	ft_init_data(&data, info);
	mlx_hook(data.mlx_w, 2, (1L << 0), *ft_press_key, &data);
	mlx_hook(data.mlx_w, 3, (1L << 1), *ft_release_key, &data);
	mlx_loop_hook(data.mlx, &ft_raycasting, &data);
	mlx_hook(data.mlx_w, 17, 0, &ft_close, &data);
	mlx_loop(data.mlx);
}
