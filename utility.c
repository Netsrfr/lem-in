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

#include "lem_in.h"

void	ft_print_error(char *error)
{
	ft_printf("error: lem-in: %s\n", error);
	exit(-1);
}

void	ft_free(t_room *rooms, t_link *links)
{
	int	i;

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

void	ft_free_map(t_map map, int argc, char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (argc > 1 && ft_strcmp(argv[1], "-c") == 0)
		flag = 1;
	ft_printf("%d\n", g_ants);
	while (i < map.size)
	{
		if (flag == 1 || map.map[i][0] != '#')
			ft_printf("%s\n", map.map[i]);
		else if (ft_strcmp(map.map[i], "##start") == 0 ||
				ft_strcmp(map.map[i], "##end") == 0 ||
				ft_strcmp(map.map[i], "##collapse") == 0)
			ft_printf("%s\n", map.map[i]);
		free(map.map[i]);
		i++;
	}
	ft_printf("\n");
	free(map.map[0]);
	free(map.map);
}
