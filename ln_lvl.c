/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ln_lvl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:32:55 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/10 14:38:45 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		lvls(t_lemin *el, t_rooms *tmp, int k, int i)
{
	t_links		*links;

	ft_printf("%s", el->prnt);
	while (k > 0 && (tmp = el->rms) == el->rms)
	{
		while (tmp)
		{
			if (tmp->lvl == i && (links = tmp->links) == tmp->links)
				while (links)
				{
					if (links->room->busy != 1)
					{
						links->room->lvl = i + 1;
						links->room->busy = 1;
						k++;
					}
					links = links->next;
				}
			tmp = tmp->next;
		}
		++i;
		k = k == 1 ? -1 : 1;
	}
	ways(el, el->rms, NULL);
	el->ways ? ways_ants(el) : 0;
}

void		nul_struct(t_lemin *el)
{
	el->rms = NULL;
	el->start = -1;
	el->end = -1;
	el->prnt = NULL;
	el->ways = NULL;
	el->s_str = NULL;
	el->end_str = NULL;
	el->lnk = 0;
}
