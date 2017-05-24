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

void	ft_links_per_room(t_room **room, t_link *links)
{
	int	i;
	int	l_flag;
	int	r_flag;

	i = 0;
	l_flag = 0;
	r_flag = 0;
	if ((*room)->link != 0)
		l_flag = 1;
	if ((*room)->link_r != 0)
		r_flag = 1;
	while (i < g_links)
	{
		if (ft_strcmp(links[i].room, (*room)->name) == 0 && l_flag == 0)
				(*room)->link++;
		 if (ft_strcmp(links[i].link, (*room)->name) == 0 && r_flag == 0)
			(*room)->link_r++;
		i++;
	}
	if (l_flag == 0)
		(*room)->links = ft_memalloc(sizeof(t_room*) * (*room)->link);
	if (r_flag == 0)
		(*room)->links_r = ft_memalloc(sizeof(t_room*) * (*room)->link_r);
}

void	ft_link(t_room *room, t_room **rooms, t_link *links)
{
	int	i;
	int j;
	int	k;

	j = 0;
	i = 0;
	k = 0;
	ft_links_per_room(&room, links);
	while (i < g_links)
	{
		if (ft_strcmp(room->name, links[i].room) == 0)
		{
			room->links[j] = ft_create_link(*rooms, links[i].link);
			j++;
		}
		if (ft_strcmp(room->name, links[i].link) == 0)
		{
			room->links_r[k] = ft_create_link(*rooms, links[i].room);
			k++;
		}
		i++;
	}
	i = 0;
	while (i < room->link)
	{
		if (room->links[i]->link == 0)
			ft_link(room->links[i], rooms, links);
		i++;
	}
}

void	ft_find_path(t_room *room)
{
	t_room	*path;
	int		i;

	i = 0;
	path = ft_memalloc(sizeof(t_room));
	path->dist = room->dist;
	while (i < room->link_r)
	{
		if(room->links_r[i]->dist < path->dist)
		{
			free(path);
			path = room->links_r[i];
		}
		i++;
	}
	path->path = 1;
	if (room->dist > 1)
		ft_find_path(path);
}

void	ft_calculate(t_room *room, int distance)
{
	int	i;
	int	j;

	i = 0;
	room->dist = distance;
	while (i < room->link)
	{
		if (room->links[i]->dist == 0)
		ft_calculate(room->links[i], distance + 1);
		i++;
	}
}

void	ft_check_path(t_room *rooms)
{
	int i;

	i = 0;
	while (rooms[i].start == 0)
		i++;
	if (rooms[i].dist == 0)
		ft_print_error("no path available from start to end");
	rooms[i].path = 1;
	ft_find_path(&rooms[i]);
}

void	ft_solve(t_room *rm, t_room *end)
{
	int	i;

	i = 0;
	while (rm->links[i]->path != 1)
		i++;
	if (rm->links[i]->ant == 0 && rm->ant < g_ants && rm->links[i]->start == 0)
		ft_solve(rm->links[i], end);
	if (rm->links[i]->ant > 0 && rm->ant < g_ants)
	{
		rm->ant = rm->links[i]->ant;
		ft_printf("L%d-%s ", rm->ant, rm->name);
		ft_solve(rm->links[i], end);
	}
	else if (rm->links[i]->start == 1)
	{
		if (rm->ant < g_ants)
		{
			rm->ant++;
			ft_printf("L%d-%s ", rm->ant, rm->name);
		}
		printf("\n");
		ft_solve(end, end);
	}
	if (rm->links[i]->start == 0 && end->ant < g_ants)
		ft_solve(rm->links[i], end);
}

void	ft_generate_farm(t_room *rooms, t_link *links)
{
	int i;

	i = 0;
	while (rooms[i].end == 0)
		i++;
	ft_link(&rooms[i], &rooms, links);
	ft_calculate(&rooms[i], 0);
	ft_check_path(rooms);
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