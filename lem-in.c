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


int		ft_count_ants(t_map map)
{
	int i;

	i = 0;
	while (i < ft_strlen(map.map[0]))
	{
		if (map.map[0][i] < '0' || map.map[0][i] > '9')
			ft_print_error("no ants specified or format incorrect");
		i++;
	}
	return((int)ft_atoi(map.map));
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
	printf("rooms = %d\n", g_rooms);
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

void	ft_validate_commands(t_map map)
{
	int i;

	i = 1;
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
		}
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
	i = 0;
	while (map[i] != ' ')
	{
		room->name[i] = map[i];
		i++;
	}
}

void	ft_get_rooms(t_map map)
{
	int i;
	int	j;
	int flag;
	t_room	*rooms;

	i = 1;
	j = 0;
	flag = 0;
	rooms = ft_memalloc(sizeof(t_room) * g_rooms);
	while (ft_strchr(map.map[i], '-') == 0)
	{
		while(map.map[i][0] == '#')
		{
			i++;
			flag = 1;
		}
		ft_get_name(map.map[i], &rooms[j]);
		if (flag == 1)
		{
			flag = 0;
			rooms[j].start = ft_strcmp(map.map[i - 1], "##start") == 0 ? 1 : 0;
			rooms[j].end = ft_strcmp(map.map[i - 1], "##end") == 0 ? 1 : 0;
		}
		j++;
		i++;
	}
	printf("start = %d, end = %d", rooms[10].start, rooms[10].end);
}

void	ft_parse_map()
{
	t_map	map;

	ft_read_stdin(&map);
	//MAP_TEST(map);
	ft_count_ants(map);
	ft_count_rooms(map);
	ft_count_links(map);
	if (g_links == 0)
		ft_print_error("invalid map: no tunnels");
	ft_validate_commands(map);
	ft_get_rooms(map);
}

int		main(int argc, char **argv)
{
	ft_parse_map();

	return (0);
}