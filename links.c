/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 19:05:17 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/25 19:05:17 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void	ft_fill_link(char *map, t_link *link)
{
	int i;
	int j;

	i = 0;
	j = 0;
	link->room = ft_memalloc(sizeof(char) * ft_strlen(map));
	link->link = ft_memalloc(sizeof(char) * ft_strlen(map));

	while (map[i] != '-')
	{
		link->room[j] = map[i];
		i++;
		j++;
	}
	i++;
	j = 0;
	while (map[i])
	{
		link->link[j] = map[i];
		i++;
		j++;
	}
}

static t_room	*ft_create_link(t_room *rooms, char *name)
{
	int i;

	i = 0;
	while (ft_strcmp(rooms[i].name, name) != 0)
		i++;
	return (&rooms[i]);
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
		if (map.map[i][0] != '#')
		{
			ft_fill_link(map.map[i], &links[j]);
			j++;
		}
		i++;
	}
	return (links);
}

void	ft_links_per_room(t_room **rooms, t_link *links)
{
	int	i;
	int	j;

	j = 0;
	while (j < g_rooms)
	{
		i = 0;
		while (i < g_links)
		{
			if (ft_strcmp(links[i].room, (*rooms)[j].name) == 0)
				(*rooms)[j].link++;
			if (ft_strcmp(links[i].link, (*rooms)[j].name) == 0)
				(*rooms)[j].link++;
			i++;
		}
		if((*rooms)[j].link != 0)
			(*rooms)[j].links = ft_memalloc(sizeof(t_room*) * (*rooms)[j].link);
		j++;
	}
}

void	ft_link(t_room **rooms, t_link *links, int i)
{
	int	j;
	int k;

	k = 0;
	j = 0;
	while (j < g_links)
	{
		if (ft_strcmp((*rooms)[i].name, links[j].room) == 0)
		{
			(*rooms)[i].links[k] = ft_create_link(*rooms, links[j].link);
			k++;
		}
		if (ft_strcmp((*rooms)[i].name, links[j].link) == 0)
		{
			(*rooms)[i].links[k] = ft_create_link(*rooms, links[j].room);
			k++;
		}
		j++;
	}
	if (i < g_rooms - 1)
		ft_link(rooms, links, i + 1);
}
