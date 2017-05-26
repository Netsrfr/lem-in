/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 19:22:07 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/25 19:22:07 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	ft_print_error(char *error)
{
	ft_printf("error: lem-in: %s\n", error);
	exit(-1);
}

void	ft_free(t_room *rooms, t_link *links)
{
	int i;

	i = 0;
	while (i < g_rooms)
	{
		if (rooms[i].link != 0)
			free(rooms[i].links);
		free(rooms[i].name);
		i++;
	}
	free(rooms);
	i = 0;
	while (i < g_links)
	{
		free(links[i].link);
		free(links[i].room);
		i++;
	}
	free(links);
}

void	ft_free_map(t_map map)
{
	int i;

	i = 1;
	ft_printf("%d\n", g_ants);
	while (i < map.size)
	{
		if (map.map[i][0] != '#')
			ft_printf("%s\n", map.map[i]);
		else if (ft_strcmp(map.map[i], "##start") == 0 ||
				 ft_strcmp(map.map[i], "##end") == 0)
			ft_printf("%s\n", map.map[i]);
		free(map.map[i]);
		i++;
	}
	ft_printf("\n");
	free(map.map);
}
