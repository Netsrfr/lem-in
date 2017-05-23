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

typedef struct		s_room
{
	char	*name;
	char	*comment;
	int		ant;
	int		start;
	int		end;
	int		cmd;
	int 	com;
	int		*links;

}					t_room;

int	g_start;
int	g_end;
int	g_rooms;
int	g_links;
int	g_hash;

#endif
