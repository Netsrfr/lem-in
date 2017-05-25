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

void	ft_print_error(char *error)
{
	ft_printf("error: lem-in: %s\n", error);
	exit(-1);
}


char	**ft_expand_map(char **map, int count)
{
	char	**temp;
	int		i;

	i = 0;
	temp = ft_memalloc(sizeof(char *) * count);
	while (i < count)
	{
		temp[i] = ft_strdup(map[i]);
		free(map[i]);
		i++;
	}
	free(map);
	i = 0;
	map = ft_memalloc(sizeof(char *) * count + 1);
	while (i < count)
	{
		map[i] = ft_strdup(temp[i]);
		free(temp[i]);
		i++;
	}
	free(temp);
	return (map);
}

void	ft_read_stdin(t_map *map)
{
	char	*line;

	map->size = 0;
	map->map = ft_memalloc(sizeof(char*));
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strcmp(line, "") == 0)
			ft_print_error("invalid map: empty parameter");
		if (map->size >= 1)
			map->map = ft_expand_map(map->map, map->size);
		map->map[map->size] = ft_strdup(line);
		map->size++;
		free(line);
	}
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


void		ft_count_ants(t_map map)
{
	int i;

	i = 0;
	while (i < ft_strlen(map.map[0]))
	{
		if (map.map[0][i] < '0' || map.map[0][i] > '9')
			ft_print_error("no ants specified or format incorrect");
		i++;
	}
	g_ants = (int)ft_atoi(map.map);
	if (g_ants == 0)
		ft_print_error("no ants specified");
}

void	ft_validate_room(char *room)
{
	int    i;
	int    j;
	int    spaces;

	i    = 0;
	spaces = 0;
	while (room[i])
	{
		if (room[i] == ' ')
			spaces++;
		i++;
	}
	if (spaces != 2)
		ft_print_error("rooms must have three parameters");
	while (*room != ' ')
		room++;
	while(*room)
	{
		if (*room != ' ' && (*room < '0' || *room > '9'))
			ft_print_error("room coordinates must be integer");
		if (*room == ' ' && (*(room + 1) == ' ' || *(room + 1) == '\0'))
			ft_print_error("parameters must be separated by single space");
		room++;
	}
}

void	ft_count_rooms(t_map map)
{
	int i;

	i = 1;
	while (ft_strchr(map.map[i], '-') == 0 && i < map.size)
	{

		while(map.map[i][0] == '#')
			i++;
		ft_validate_room(map.map[i]);
		g_rooms++;
		i++;
	}
	if (g_rooms == 0)
		ft_print_error("invalid map: no rooms");
}

void	ft_count_links(t_map map)
{
	int i;
	int	j;
	int	links;

	i = 1;
	while (ft_strchr(map.map[i], '-') == 0)
		i++;
	while (i < map.size)
	{
		links = 0;
		j = 0;
		while(map.map[i][0] == '#')
			i++;
		while(map.map[i][j])
		{
			if (map.map[i][j] == '-')
				links++;
			j++;
		}
		if (links != 1)
			ft_print_error("parameter must have one link");
		g_links++;
		i++;
	}
}

void	ft_validate_commands(t_map map, int i, int start, int end)
{
	while (i < map.size)
	{
		if (ft_strcmp(map.map[i], "##start") == 0 ||
				ft_strcmp(map.map[i], "##end") == 0)
		{
			if (i == map.size - 1)
				ft_print_error("must issue command to parameter");
			if (map.map[i + 1][0] == '#')
				ft_print_error("cannot issue command to a comment or command");
			if(ft_strchr(map.map[i + 1], '-') != 0)
				ft_print_error("must issue command to room");
			if (ft_strcmp(map.map[i], "##start") == 0)
				start = 1;
			if (ft_strcmp(map.map[i], "##end") == 0)
				end = 1;
		}
		i++;
	}
	if (start == 0 || end == 0)
		ft_print_error("ant farm must have a start and end");
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
		while(map.map[i][0] == '#')
			i++;
		ft_get_name(map.map[i], &rooms[j]);
		if (i > 1)
		{
			rooms[j].start = ft_strcmp(map.map[i - 1], "##start") == 0 ? 1 : 0;
			rooms[j].end = ft_strcmp(map.map[i - 1], "##end") == 0 ? 1 : 0;
		}
		j++;
		i++;
	}
	return (rooms);
}

void	ft_fill_link(char *map, t_link *link)
{
	int i;
	int j;

	i = 0;
	j = 0;
	link->room = ft_memalloc(sizeof(map));
	link->link = ft_memalloc(sizeof(map));
	while (map[i] != '-')
	{
		link->room[j] = map[i];
		i++;
		j++;
	}
	i++;
	j = 0;
	while (map[i] && map[i] != '-')
	{
		link->link[j] = map[i];
		i++;
		j++;
	}
}

t_link	*ft_get_links(t_map map)
{
	int i;
	int	j;
	t_link *links;

	i = 1;
	j = 0;
	links = ft_memalloc(sizeof(t_link) * g_links);
	while (ft_strchr(map.map[i], '-') == 0)
		i++;
	while (i < map.size)
	{
		while (map.map[i][0] == '#')
			i++;
		ft_fill_link(map.map[i], &links[j]);
		i++;
		j++;
	}
	return (links);
}

void	ft_validate_rooms(t_room *rooms)
{
	int i;
	int j;

	i = 0;
	while (i < g_rooms)
	{

		j = i + 1;
		while (j < g_rooms)
		{
			if (rooms->name[0] == 'L')
				ft_print_error("room cannot start with 'L'");
			if (ft_strcmp(rooms[i].name, rooms[j].name) == 0)
				ft_print_error("room duplicate provided");

			j++;
		}
		i++;
	}
}

void	ft_validate_links(t_room *rooms, t_link *links)
{
	int i;
	int j;
	int room;
	int	link;

	i = 0;
	while (i < g_links)
	{
		room = 0;
		link = 0;
		j = 0;
		while (j < g_rooms)
		{
			if (ft_strcmp(links[i].room, rooms[j].name) == 0)
				room = 1;
			if (ft_strcmp(links[i].link, rooms[j].name) == 0)
				link = 1;
			j++;
		}
		if (link == 0 || room == 0)
			ft_print_error("invalid room name in link");
		if (ft_strcmp(links[i].room, links[i].link) == 0)
			ft_print_error("cannot link room to itself");
		i++;
	}
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

t_room	*ft_create_link(t_room *rooms, char *name)
{
	int i;

	i = 0;
	while (ft_strcmp(rooms[i].name, name) != 0)
		i++;
	return (&rooms[i]);
}

//TODO: WORKING
//void	ft_links_per_room(t_room **rooms, t_link *links)
//{
//	int	i;
//	int	j;
//
//	j = 0;
//	while (j < g_rooms)
//	{
//		i = 0;
//		while (i < g_links)
//		{
//			if (ft_strcmp(links[i].room, (*rooms)[j].name) == 0)
//				(*rooms)[j].link++;
//			if (ft_strcmp(links[i].link, (*rooms)[j].name) == 0)
//				(*rooms)[j].link_r++;
//			i++;
//		}
//		if(rooms[j]->link != 0)
//			(*rooms)[j].links = ft_memalloc(sizeof(t_room*) * (*rooms)[j].link);
//		if(rooms[j]->link_r != 0)
//			(*rooms)[j].links_r = ft_memalloc(sizeof(t_room*) * (*rooms)[j].link_r);
//		j++;
//	}
//}

//void	ft_link(t_room **rooms, t_link *links, int i)
//{
//	int	j;
//	int k;
//	int	l;
//
//	k = 0;
//	j = 0;
//	l = 0;
////	printf("FTLINK START\n");
//	while (j < g_links)
//	{
////		printf("i = %d\n", j);
//		if (ft_strcmp((*rooms)[i].name, links[j].room) == 0)
//		{
////			printf("j = %d\n", k);
//			(*rooms)[i].links[k] = ft_create_link(*rooms, links[j].link);
//			k++;
//		}
//		if (ft_strcmp((*rooms)[i].name, links[j].link) == 0)
//		{
////			printf("k = %d\n", l);
//			(*rooms)[i].links_r[l] = ft_create_link(*rooms, links[j].room);
//			l++;
//		}
//		j++;
//	}
//	if (i < g_rooms - 1)
//		ft_link(rooms, links, i + 1);
////	printf("FTLINK END\n");
//}
//void		ft_find_distance_r(t_room *room, int distance)
//{
//	int i;
//	int j;
//
//	i = 0;
//	j = 0;
//
//	if(room->dist == 0)
//		room->dist = distance;
//	else
//		room->dist = distance > room->dist ? room->dist : distance;
//	while(i < room->link_r)
//	{
////		printf("room[%d] = %s | room dist = %d\n", j, room->links_r[i]->name, room->links_r[i]->dist);
//		j = 0;
//		while (j < room->link)
//		{
////			printf("room_r[%d] = %s | room_r dist = %d\n", j, room->links[j]->name, room->links[j]->dist);
//			if (room->links[j]->flag == 0 && room->links[j]->end == 0)
//			{
//				room->links[j]->flag = 1;
//				ft_find_distance(room->links[j], distance + 1);
//			}
//			j++;
//		}
//		if (room->links_r[i]->flag_r == 0 && room->links_r[i]->end == 0)
//		{
//			room->links_r[i]->flag_r = 1;
//			ft_find_distance_r(room->links_r[i], distance + 1);
//		}
////		printf("\n");
//		i++;
//	}
//}
//
//void		ft_find_distance(t_room *room, int distance)
//{
//	int i;
//	int j;
//
//	i = 0;
//	j = 0;
//	if(room->dist == 0)
//		room->dist = distance;
//	else
//		room->dist = distance > room->dist ? room->dist : distance;	while(i < room->link)
//	{
////		printf("room[%d] = %s | room dist = %d\n", j, room->links[i]->name, room->links[i]->dist);
//		j = 0;
//		while (j < room->link_r)
//		{
////			printf("room_r[%d] = %s | room_r dist = %d\n", j, room->links_r[j]->name, room->links_r[j]->dist);
//			if (room->links_r[j]->flag_r == 0 && room->links_r[j]->end == 0)
//			{
//				room->links_r[j]->flag_r = 1;
//				ft_find_distance_r(room->links_r[j], distance + 1);
//			}
//			j++;
//		}
//		if (room->links[i]->flag == 0 && room->links[i]->end == 0)
//		{
//			room->links[i]->flag = 1;
//			ft_find_distance(room->links[i], distance + 1);
//		}
////		printf("\n");
//		i++;
//	}
//}
//void	ft_find_path(t_room *room)
//{
//	t_room	*path;
//	int		i;
//	printf("FINDPATH - START\n");
//	ROOM_TEST(*room, 1);
//	//ROOM_TEST(*room->links[0], 0);
//	i = 0;
////	path = ft_memalloc(sizeof(t_room*));
//	path = ft_memalloc(sizeof(t_room));
//	path->dist = room->dist;
//	printf("TESTTEST\n");
//	while (i < room->link_r)
//	{
//		//ROOM_TEST(*room->links_r[i], 0);
//		if(room->links_r[i]->dist != 0 && room->links_r[i]->dist < path->dist)
//		{
//			printf("TEST\n");
//			//free(path);
//			path = room->links_r[i];
//		}
//		//	ft_find_path_r(room->links_r[i]);
//		i++;
//	}
//	i = 0;
//	while (i < room->link)
//	{
//		printf("distance = %d | path distance = %d\n", room->links[0]->dist, path->dist);
//		if(room->links[i]->dist != 0 && room->links[i]->dist < path->dist)
//		{
//			printf("LINKS\n");
////			free(path);
//			printf("LINKS2\n");
//			//	free(*path);
//			path = room->links[i];
//			printf("distance = %d | path distance = %d\n", room->links[0]->dist, path->dist);
//
//		}
//		i++;
//	}
//
//	printf("****  PATH_TEST  ****\n");
//	ROOM_TEST(*path, 1);
//	path->path = 1;
//	if (room->dist > 1)
//		ft_find_path(path);
//	printf("FINDPATH - END\n");
//}
//TODO: END WORKING

void	ft_links_per_room(t_room **rooms, t_link *links)
{
	int	i;
	int	j;
	ROOMS_TEST(*rooms, 0);
	j = 0;
	while (j < g_rooms)
	{
		i = 0;
		printf("j = %d\n", j);
		while (i < g_links)
		{
			printf("i = %d\n", i);
			if (ft_strcmp(links[i].room, (*rooms)[j].name) == 0)
				(*rooms)[j].link++;
			if (ft_strcmp(links[i].link, (*rooms)[j].name) == 0)
				(*rooms)[j].link++;
			i++;
		}
		printf("links = %d\n", (*rooms)[j].link);
		ROOM_TEST((*rooms)[j], 0);
		if((*rooms)[j].link != 0)
			(*rooms)[j].links = ft_memalloc(sizeof(t_room*) * (*rooms)[j].link);
		printf("TEST\n");
		j++;
	}
}

void	ft_link(t_room **rooms, t_link *links, int i)
{
	int	j;
	int k;
	int	l;

	k = 0;
	j = 0;
	l = 0;
	printf("FTLINK START\n");
	while (j < g_links)
	{
//		printf("i = %d\n", j);
		if (ft_strcmp((*rooms)[i].name, links[j].room) == 0)
		{
//			printf("j = %d\n", k);
			(*rooms)[i].links[k] = ft_create_link(*rooms, links[j].link);
			k++;
		}
		if (ft_strcmp((*rooms)[i].name, links[j].link) == 0)
		{
//			printf("k = %d\n", l);
			(*rooms)[i].links[k] = ft_create_link(*rooms, links[j].room);
			k++;
		}
		j++;
	}
	if (i < g_rooms - 1)
		ft_link(rooms, links, i + 1);
//	printf("FTLINK END\n");
}

void		ft_find_distance(t_room *room, int distance)
{
	int i;
	int j;

	i = 0;
	j = 0;

	if(room->dist == 0)
		room->dist = distance;
	else
		room->dist = distance > room->dist ? room->dist : distance;
	while(i < room->link)
	{
//			printf("room_r[%d] = %s | room_r dist = %d\n", j, room->links[j]->name, room->links[j]->dist);
		if (room->links[i]->flag == 0 && room->links[i]->end == 0)
		{
			room->links[i]->flag = 1;
			ft_find_distance(room->links[i], distance + 1);
		}
//		printf("\n");
		i++;
	}
}

void	ft_find_path(t_room *room)
{
	t_room	*path;
	int		i;
	printf("FINDPATH - START\n");
	ROOM_TEST(*room, 1);
	//ROOM_TEST(*room->links[0], 0);
	i = 0;
//	path = ft_memalloc(sizeof(t_room*));
	path = ft_memalloc(sizeof(t_room));
	path->dist = room->dist;
	printf("TESTTEST\n");
	while (i < room->link)
	{
		printf("distance = %d | path distance = %d\n", room->links[0]->dist, path->dist);
		if(room->links[i]->dist != 0 && room->links[i]->dist < path->dist)
		{
			printf("LINKS\n");
//			free(path);
			printf("LINKS2\n");
		//	free(*path);
			path = room->links[i];
			printf("distance = %d | path distance = %d\n", room->links[0]->dist, path->dist);
		}
		i++;
	}
	printf("****  PATH_TEST  ****\n");
	ROOM_TEST(*path, 1);
	path->path = 1;
	if (room->dist > 1)
		ft_find_path(path);
	printf("FINDPATH - END\n");
}

void	ft_calculate_r(t_room *rooms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < g_rooms)
	{
		while (i < rooms[j].link_r)
		{
			if (rooms[j].links_r[i]->dist != 0)
			{
				if (rooms[j].dist == 0)
				{
					rooms[j].dist = rooms[j].links_r[i]->dist + 1;
					i = 0;
				}
			}
			i++;
		}
		j++;
	}
}

//void	ft_calculate_r(t_room *room, int distance)
//{
//	int	i;
//
//	i = 0;
//	room->dist = distance;
//	while (i < room->link_r)
//	{
//		if (room->links_r[i]->dist == 0 && room->links_r[i]->end == 0)
//			ft_calculate_r(room->links[i], distance + 1);
//		i++;
//	}
//}

//void	ft_calculate(t_room *room, int distance)
//{
//	int	i;
//
//	i = 0;
//	room->dist = distance;
//	while (i < room->link)
//	{
//		if (room->links[i]->dist == 0)
//			ft_calculate(room->links[i], distance + 1);
//		i++;
//	}
//	i = 0;
//	distance = 0;
//	while (i < room->link_r)
//	{
//		if (room->links_r[i]->dist == 0)
//			ft_calculate(room->links_r[i], distance + 1);
//		i++;
//	}
//}

//void	ft_calculate(t_room *room, int distance)
//{
//	int	i;
////	printf("CALCULATE - START\n");
//	i = 0;
//	room->dist = distance;
//	while (i < room->link)
//	{
//		if (room->links[i]->dist == 0)
//			ft_calculate(room->links[i], distance + 1);
//		i++;
//	}
//	i = 0;
//	//distance = 0;
//	while (i < room->link_r)
//	{
//		if (room->links_r[i]->dist == 0)
//			ft_calculate(room->links_r[i], distance + 1);
//		i++;
//	}
////	printf("CALCULATE - END\n");
//}

void	ft_direct(t_room *rooms)
{
	int	end;
	int	i;

	end = 0;
	i = 0;
	while (rooms[end].start == 0)
		end++;
	while (i++ < g_ants)
		ft_printf("L%d-%s ", i, rooms[end].name);
	ft_printf("\n");
	exit(0);
}

void	ft_check_path(t_room *rooms)
{
	int i;
//	printf("CHECKPATH - START\n");
	i = 0;
//	printf("cp_room = %s\n", rooms[i].name);
	while (rooms[i].start == 0)
		i++;
//	printf("cp_room = %s\n", rooms[i].name);
	if (rooms[i].dist == 0)
		ft_print_error("no path available from start to end");
	if (rooms[i].dist == 1)
		ft_direct(rooms);
	rooms[i].path = 1;
//	printf("cp_room = %s\n", rooms[i].name);
	printf("BEFORE_FINDPATH\n");
	ft_find_path(&rooms[i]);
	printf("AFTER_FINDPATH\n");
	ROOMS_TEST(rooms, 1);
//	printf("CHECKPATH - END\n");

//	i = 0;
//	while (i < g_rooms)
//	{
//		if (ft_find_path_r(&rooms[i]))
//			i = 0;
//		i++;
//	}
}

//void	ft_shortest(t_room *room)
//{
//	int	i;
//	char	*path;
//
//	i = 0;
//	path = ft_memalloc(sizeof(t_room));
//	while (i < g_links)
//	{
//		while (room->links[i]->path != 1)
//			i++;
//	}
//}

void	ft_solve(t_room *rm, t_room *end)
{

	int	i;
//	printf("SOLVE - START\n");
	i = 0;
//	printf("SOLVE1\n");
//	printf("room = %s\n", rm->name);
	while (rm->links[i]->path != 1 || rm->links[i]->dist < rm->dist)
	{
//		printf("links[%d] = %s | path = %d\n",i, rm->links[i]->name, rm->links[i]->path);
		i++;
	}
//	printf("SOLVE2\n");
	if (rm->links[i]->ant == 0 && rm->ant < g_ants && rm->links[i]->start == 0)
		ft_solve(rm->links[i], end);
//	printf("SOLVE3\n");
	if (rm->links[i]->ant > 0 && rm->ant < g_ants)
	{
		rm->ant = rm->links[i]->ant;
		ft_printf("L%d-%s ", rm->ant, rm->name);
		ft_solve(rm->links[i], end);
	}
	else if (rm->links[i]->start == 1)
	{
//		printf("SOLVE4\n");
		if (rm->ant < g_ants)
		{
			rm->ant++;
			ft_printf("L%d-%s ", rm->ant, rm->name);
		}
		ft_printf("\n");
		ft_solve(end, end);
	}
//	printf("SOLVE5\n");
	if (rm->links[i]->start == 0 && end->ant < g_ants)
		ft_solve(rm->links[i], end);
//	printf("SOLVE - END\n");
}

void	ft_generate_farm(t_room *rooms, t_link *links)
{
	int i;
	int j;

	i = 0;
	while (rooms[i].end == 0)
		i++;
	printf("BEFORE_LPR\n");

	ft_links_per_room(&rooms, links);
	ft_link(&rooms, links, 0);
	printf("BEFORE_DISTANCE\n");
	ft_find_distance(&rooms[i], 0);
	printf("AFTER_DISTANCE\n");
//	ft_find_distance_r(&rooms[i], 0);
//	printf("AFTER_DISTANCE_R\n");
	ft_check_path(rooms);
	printf("AFTER_CHECKPATH\n");
	ROOMS_TEST(rooms, 1);
	ft_solve(&rooms[i], &rooms[i]);
	ft_printf("\n");
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

void	ft_parse_map()
{
	t_map	map;
	t_room	*rooms;
	t_link	*links;

	ft_read_stdin(&map);
	ft_count_ants(map);
	ft_count_rooms(map);
	ft_count_links(map);
	if (g_links == 0)
		ft_print_error("invalid map: no tunnels");
	ft_validate_commands(map, 1, 0, 0);
	rooms = ft_get_rooms(map);
	ft_validate_rooms(rooms);
	links = ft_get_links(map);
	ft_validate_links(rooms, links);
//	MAP_TEST(map);
	ft_free_map(map);
	ft_generate_farm(rooms, links);
	ft_free(rooms, links);
}

int		main(int argc, char **argv)
{
	ft_parse_map();

	return (0);
}