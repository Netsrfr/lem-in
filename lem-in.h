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
	int				dist;
	struct	s_room	**links;
}					t_room;


int	g_start;
int	g_end;
int	g_rooms;
int	g_links;
int	g_hash;

void				ft_link(t_room *room, t_room **rooms, t_link *links);

#endif
