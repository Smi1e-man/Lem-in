/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 12:42:37 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/04 14:12:42 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEMIN_H
# define __LEMIN_H

# include "libft/includes/libft.h"

/*
**	struct
*/
typedef struct s_links			t_links;
typedef struct s_rms			t_rooms;
typedef struct s_path			t_path;
typedef struct s_ways			t_ways;
typedef struct s_lemin			t_lemin;

struct				s_links
{
	t_rooms			*room;
	struct s_links	*next;
};

struct				s_rms
{
	char			*name;
	t_links			*links;
	int				index;
	int				lvl;
	int				busy;
	int				xy[2];

	struct s_rms	*next;
};

struct				s_path
{
	t_rooms			*room;
	struct s_path	*next;
};

struct				s_ways
{
	int				length;
	t_path			*path;

	struct s_ways	*next;
};

struct				s_lemin
{
	int				ants;
	int				start;
	int				end;
	t_rooms			*rms;
	t_ways			*ways;
};

/*
**	lem-in function
*/
void				lvls(t_lemin *el, t_rooms *tmp, int k, int i);

#endif