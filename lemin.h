/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 12:42:37 by seshevch          #+#    #+#             */
/*   Updated: 2019/01/28 18:43:22 by seshevch         ###   ########.fr       */
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
	int				index;

	struct s_rms	*next;

}					t_rooms;

typedef struct		s_lemin
{
	char			**rooms;

	char			**links;

	int				ants;

	int				start;
	int				end;

	t_rooms			*rms;

}					t_lemin;


#endif