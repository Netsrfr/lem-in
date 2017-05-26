/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 09:19:09 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/23 09:19:09 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft/libft.h"
# include "libraries/ft_printf/ft_printf.h"
# include "libraries/get_next_line/get_next_line.h"

typedef struct		s_map
{
	char	**map;
	int		size;
}					t_map;

typedef struct		s_link
{
	char	*room;
	char	*link;
}					t_link;

typedef struct		s_room
{
	char			*name;
	int				ant;
	int				start;
	int				end;
	int				link;
	int				link_r;
	int				dist;
	int				flag;
	int				path;
	struct	s_room	**links;
	struct	s_room	**links_r;

}					t_room;

int	g_rooms;
int	g_links;
int	g_ants;

/*
** parse_map.c
*/
void	ft_get_map(t_map *map);

/*
** links.c
*/
t_link	*ft_get_links(t_map map);
void	ft_links_per_room(t_room **rooms, t_link *links);
void	ft_link(t_room **rooms, t_link *links, int i);

/*
** path.c
*/
void	ft_find_distance(t_room *room, int distance);
void	ft_solve(t_room *rm, t_room *end);
void	ft_check_path(t_room *rooms);

/*
** utility.c
*/
void	ft_print_error(char *error);
void	ft_free(t_room *rooms, t_link *links);
void	ft_free_map(t_map map);


/*
** validation.c
*/
void	ft_validate_room(char *room);
void	ft_validate_rooms(t_room *rooms);
void	ft_validate_commands(t_map map, int i, int start, int end);
void	ft_validate_links(t_room *rooms, t_link *links);

#endif
