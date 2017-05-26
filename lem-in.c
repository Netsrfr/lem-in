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

#include "lem-in.h"

void	ROOMS_TEST(t_room *rooms, int links)
{
	int i;
	int j;

	i = 0;
	printf("    *****   ROOMS TEST   *****    ");
	while (i < g_rooms)
	{
		j = 0;
		printf("ROOM[%d] = %s | links = %d | links_r = %d | distance = %d | path = %d\n", i, rooms[i].name, rooms[i].link, rooms[i].link_r, rooms[i].dist, rooms[i].path);
		while (links == 1 && j < rooms[i].link)
		{
			printf("LINK = %s\n", rooms[i].links[j]->name);
			j++;
		}
		j = 0;
		while (links == 1 && j < rooms[i].link_r)
		{
			printf("LINK_R = %s\n", rooms[i].links_r[j]->name);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("    *****    END TEST    *****    \n\n");
}

void	ROOM_TEST(t_room room, int links)
{
	int	j;

	j = 0;
	printf("    *****   ROOM TEST   *****    \n");
	printf("ROOM = %s | links = %d | links_r = %d | distance = %d | path = %d\n", room.name, room.link, room.link_r, room.dist, room.path);
	while (links == 1 && j < room.link)
	{
		printf("LINK = %s\n", room.links[j]->name);
		j++;
	}
	j = 0;
	while (links == 1 && j < room.link_r)
	{
		printf("LINK_R = %s\n", room.links_r[j]->name);
		j++;
	}
	printf("    *****   END TEST    *****    \n\n");
}



void	MAP_TEST(t_map map)
{
	int i;

	i = 0;
	while (i < map.size)
	{
		printf("map[%d] = %s\n", i, map.map[i]);
		i++;
	}
}

void	ft_get_name(char *map, t_room *room)
{
	int i;

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
	int i;
	int	j;
	t_room	*rooms;

	i = 1;
	j = 0;
	rooms = ft_memalloc(sizeof(t_room) * g_rooms);
	while (ft_strchr(map.map[i], '-') == 0)
	{
		if (map.map[i][0] != '#')
		{
			ft_get_name(map.map[i], &rooms[j]);
			if (i > 1)
			{
				rooms[j].start = ft_strcmp(map.map[i - 1], "##start") == 0 ? 1
																		   : 0;
				rooms[j].end   = ft_strcmp(map.map[i - 1], "##end") == 0 ? 1
																		 : 0;
			}
			j++;
		}
		i++;
	}
	return (rooms);
}
















void	ft_generate_farm(t_room *rooms, t_link *links)
{
	int i;

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

	ft_get_map(&map);
	ft_validate_commands(map, 1, 0, 0);
	rooms = ft_get_rooms(map);
	ft_validate_rooms(rooms);
	links = ft_get_links(map);
	ft_validate_links(rooms, links);
	ft_free_map(map);
	ft_links_per_room(&rooms, links);
	ft_link(&rooms, links, 0);
	ft_generate_farm(rooms, links);
	ft_free(rooms, links);
	exit(0);
}