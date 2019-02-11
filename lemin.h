/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 12:42:37 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/11 13:11:29 by seshevch         ###   ########.fr       */
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
typedef struct s_prnt			t_prnt;

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

	struct s_rms	*next;
};

struct				s_path
{
	t_rooms			*room;
	int				busy;
	int				numb_ant;
	struct s_path	*next;
};

struct				s_ways
{
	int				length;
	int				ants;
	int				a_on_th;
	t_path			*path;

	struct s_ways	*next;
};

struct				s_prnt
{
	char			*str;

	struct s_prnt	*next;
};


struct				s_lemin
{
	t_rooms			*str;
	t_rooms			*end_str;
	t_prnt			*prnt;
	t_prnt			*end_prnt;

	int				lnk;
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
void				ways(t_lemin *el, t_rooms *end, t_rooms *r_min_lvl);
void				ways_ants(t_lemin *el);
void				add_way(t_lemin *el, t_ways *tmp);
void				dell_way(t_ways *tmp);
void				validate_room(char	*line, char **str, t_rooms *tmp);
void				validate_link(char **str, t_rooms *room_head);
int					ft_numbs(char *str);
void				ft_prnt_n_join(t_lemin *el, char *part, int	v);
void				nul_struct(t_lemin *el);
void				room_add(t_rooms **tmp, char **r, t_lemin *el,
							t_rooms *list);
void				room_link(t_rooms **tmp, t_lemin *el, char *l);
void				ft_error(void);

#endif
