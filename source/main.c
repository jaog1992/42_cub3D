/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-orma <jde-orma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:51:41 by jde-orma          #+#    #+#             */
/*   Updated: 2024/09/05 00:51:41 by jde-orma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/* initializes the cub struct with a hardcoded map and textures */
void	ft_init_cub(t_map *map)
{
	ft_bzero(map, sizeof(t_map));
	map->start_map = 0;
	map->no = ft_strdup("assets/textures/NO.xpm");
	map->so = ft_strdup("assets/textures/SO.xpm");
	map->we = ft_strdup("assets/textures/WE.xpm");
	map->ea = ft_strdup("assets/textures/EA.xpm");
	map->imap = malloc(sizeof(int *) * 8);
	int i = 0;
	while (i < 8)
		map->imap[i++] = malloc(sizeof(int) * 20);
	i = 0;
	while (i < 19)
	{
		map->imap[0][i] = 1;
		map->imap[7][i++] = 1;
	}
	i = 0;
	while (i < 19)
	{
		map->imap[1][i] = 0;
		map->imap[2][i] = 0;
		map->imap[3][i] = 0;
		map->imap[4][i] = 0;
		map->imap[5][i] = 0;
		map->imap[6][i++] = 0;
	}
	map->imap[1][0] = 1;
	map->imap[2][0] = 1;
	map->imap[3][0] = 1;
	map->imap[4][0] = 1;
	map->imap[5][0] = 1;
	map->imap[6][0] = 1;
	map->imap[1][1] = 1;
	map->imap[2][3] = 1;
	map->imap[2][8] = 1;
	map->imap[3][8] = 1;
	map->imap[2][11] = 1;
	map->imap[3][11] = 1;
	map->imap[1][19] = 1;
	map->imap[2][19] = 1;
	map->imap[3][19] = 1;
	map->imap[4][19] = 1;
	map->imap[5][19] = 1;
	map->imap[6][19] = 1;
	map->c = 7829367;
	map->f = 3354412;
	map->map_size[0] = 5;
	map->map_size[1] = 20;
	map->player_position[X_AXIS] = 10;
	map->player_position[Y_AXIS] = 3;
	map->player_direction[X_AXIS] = 0;
	map->player_direction[Y_AXIS] = -1;
	map->start_map = 109;
}

int	main(int argc, char **argv)
{
	t_map	map;

	(void)argc;
	(void)argv;
	ft_init_cub(&map);
	ft_game(map);
	ft_free_cub("Game ended\n", &map, FREE_ALL);
	return (EXIT_SUCCESS);
}
