/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 19:11:57 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/25 19:11:57 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void		ft_find_distance(t_room *room, int distance)
{
	int i;

	i = 0;

	if(room->dist == 0)
		room->dist = distance;
	else
		room->dist = distance > room->dist ? room->dist : distance;
	while(i < room->link)
	{
		if (room->links[i]->flag == 0 && room->links[i]->end == 0)
		{
			room->links[i]->flag = 1;
			ft_find_distance(room->links[i], distance + 1);
		}
		i++;
	}
}

static void	ft_find_path(t_room *room)
{
	t_room	*path;
	int		i;
	i = 0;
	path = ft_memalloc(sizeof(t_room));
	path->dist = room->dist;
	while (i < room->link)
	{
		if(room->links[i]->dist != 0 && room->links[i]->dist < path->dist)
		{
			//	free(*path);
			path = room->links[i];
		}
		i++;
	}
	path->path = 1;
	if (room->dist > 1)
		ft_find_path(path);
}

static void	ft_direct(t_room *rooms)
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
	i = 0;
	while (rooms[i].start == 0)
		i++;
	if (rooms[i].dist == 0)
		ft_print_error("no path available from start to end");
	if (rooms[i].dist == 1)
		ft_direct(rooms);
	rooms[i].path = 1;
	ft_find_path(&rooms[i]);
}

void	ft_solve(t_room *rm, t_room *end)
{
	int	i;

	i = 0;
	while (rm->links[i]->path != 1 || rm->links[i]->dist < rm->dist)
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
		ft_printf("\n");
		ft_solve(end, end);
	}
	if (rm->links[i]->start == 0 && end->ant < g_ants)
		ft_solve(rm->links[i], end);
}
