/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 12:42:37 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/03 18:40:52 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEMIN_H
# define __LEMIN_H

# include "libft/includes/libft.h"

/*
**	struct
*/
typedef struct		s_rms
{
	char			*room;

	struct				s_rel
	{
		struct s_rms	*link;
		struct s_rel	*next;

	}					t_rel;

	struct s_rel		*links;
	struct s_rel		*first_link;

	int				index;

	int				lvl;
	int				busy;

	struct s_rms	*next;

}					t_rooms;

typedef struct				s_rms_on_path
{
	t_rooms					*rm_path;

	struct s_rms_on_path	*next;

}							t_rms_on_pth;

typedef struct		s_ways
{
	int				lenth;
	t_rms_on_pth	*rms_on_path;

	struct s_ways	*next;

}					t_ways;

typedef struct		s_lemin
{
	int				ants;

	int				start;
	int				end;

	t_rooms			*rms;
	t_ways			*ways;

}					t_lemin;

/*
**	lem-in function
*/
void				lvls(t_lemin *el, t_rooms *tmp, int k, int i);

#endif