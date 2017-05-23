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

void	ft_print_error(char *error)
{
	ft_printf("error: lem-in: %s\n", error);
	exit(-1);
}

int		ft_count_ants(t_map map)
{
	int i;

	i = 0;
	while (i < ft_strlen(map.map[0]));
	{
		if (map.map[0][i] < '0' || map.map[0][i] > '9');
			ft_print_error("no ants specified or format incorrect");
		i++;
	}
	return((int)ft_atoi(map.map));
}

void	ft_parse_map()
{
	t_map	map;

	ft_read_stdin(&map);
	ft_count_ants(map);
	MAP_TEST(map);
}

int		main(int argc, char **argv)
{
	ft_parse_map();

	return (0);
}