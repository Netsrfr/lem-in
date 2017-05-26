/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 19:00:36 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/25 19:00:36 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	ft_validate_room(char *room)
{
	int    i;
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
			ft_print_error("room coordinates must be positive integer");
		if (*room == ' ' && (*(room + 1) == ' ' || *(room + 1) == '\0'))
			ft_print_error("parameters must be separated by single space");
		room++;
	}
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
				start++;
			if (ft_strcmp(map.map[i], "##end") == 0)
				end++;
		}
		i++;
	}
	if (start != 1 || end != 1)
		ft_print_error("ant farm must have one start and one end");
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