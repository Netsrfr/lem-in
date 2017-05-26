/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 18:43:06 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/25 18:43:06 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	**ft_expand_map(char **map, int count)
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

static void	ft_read_stdin(t_map *map, int i)
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
	if (!(map->map[0]))
		ft_print_error("invalid map: empty map");
	while (i < (int)ft_strlen(map->map[0]))
	{
		if (map->map[0][i] < '0' || map->map[0][i] > '9')
			ft_print_error("no ants specified or format incorrect");
		i++;
	}
	g_ants = (int)ft_atoi(map->map);
	if (g_ants == 0)
		ft_print_error("no ants specified");
}

static void	ft_count_rooms(t_map map)
{
	int	i;

	i = 1;
	while (i < map.size && ft_strchr(map.map[i], '-') == 0)
	{
		if (map.map[i][0] != '#')
		{
			ft_validate_room(map.map[i]);
			g_rooms++;
		}
		i++;
	}
	if (g_rooms == 0)
		ft_print_error("invalid map: no rooms");
}

static void	ft_count_links(t_map map)
{
	int	i;
	int	links;

	i = 1;
	while (i < map.size && ft_strchr(map.map[i], '-') == 0)
		i++;
	while (i < map.size)
	{
		links = 0;
		while (i < map.size && map.map[i][0] == '#')
			i++;
		if (i < map.size)
		{
			if (ft_strchr(map.map[i], '-') != 0)
				links++;
			if (links != 1)
				ft_print_error("parameter must have one link");
			g_links++;
			i++;
		}
	}
	if (g_links == 0)
		ft_print_error("invalid map: no tunnels");
}

void		ft_get_map(t_map *map)
{
	ft_read_stdin(map, 0);
	ft_count_rooms(*map);
	ft_count_links(*map);
}
