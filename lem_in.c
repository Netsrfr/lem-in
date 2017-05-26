/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 09:09:47 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/23 09:09:47 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_get_name(char *map, t_room *room)
{
	int	i;

	i = 0;
	while (map[i] != ' ')
		i++;
	room->name = ft_memalloc(sizeof(char) * i + 1);
	room->ant = 0;
	i = 0;
	while (map[i] != ' ')
	{
		room->name[i] = map[i];
		i++;
	}
}

t_room	*ft_get_rooms(t_map map)
{
	int		i;
	int		j;
	t_room	*rm;

	i = 1;
	j = 0;
	rm = ft_memalloc(sizeof(t_room) * g_rooms);
	while (ft_strchr(map.map[i], '-') == 0)
	{
		if (map.map[i][0] != '#')
		{
			ft_get_name(map.map[i], &rm[j]);
			if (i > 1)
			{
				rm[j].start = ft_strcmp(map.map[i - 1], "##start") == 0 ? 1 : 0;
				rm[j].end = ft_strcmp(map.map[i - 1], "##end") == 0 ? 1 : 0;
				rm[j].w = ft_strcmp(map.map[i - 1], "##collapse") == 0 ? 1 : 0;
			}
			j++;
		}
		i++;
	}
	return (rm);
}

void	ft_generate_farm(t_room *rooms)
{
	int	i;

	i = 0;
	while (rooms[i].end == 0)
		i++;
	ft_find_distance(&rooms[i], 0);
	ft_check_path(rooms);
	ft_solve(&rooms[i], &rooms[i]);
	ft_printf("\n");
}

int		main(int argc, char **argv)
{
	t_map	map;
	t_room	*rooms;
	t_link	*links;

	argc = 0;
	argv = NULL;
	ft_get_map(&map);
	ft_validate_commands(map, 1, 0, 0);
	rooms = ft_get_rooms(map);
	ft_validate_rooms(rooms);
	links = ft_get_links(map);
	ft_validate_links(rooms, links);
	ft_free_map(map);
	ft_links_per_room(&rooms, links);
	ft_link(&rooms, links, 0);
	ft_generate_farm(rooms);
	ft_free(rooms, links);
	exit(0);
}
