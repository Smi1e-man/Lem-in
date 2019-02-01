/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 12:42:37 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/01 18:31:36 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEMIN_H
# define __LEMIN_H

# include "libft/includes/libft.h"

/*
**	struct
*/
// typedef struct		s_l
// {
// 	t_rooms			*link;
// 	struct s_l		*next;

// }					t_link;

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
	struct s_rms	*next;

}					t_rooms;

typedef struct		s_lemin
{
	int				ants;

	int				start;
	int				end;

	t_rooms			*rms;

}					t_lemin;

/*
**	lem-in function
*/

#endif