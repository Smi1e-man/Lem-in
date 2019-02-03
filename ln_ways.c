/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ln_ways.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 12:58:42 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/03 12:23:18 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		path_add(t_lemin *el, t_rooms *room_on_path)
{
	t_rms_on_pth	*tmp;

	if (el->ways->rms_on_path)
	{
		tmp = (t_rms_on_pth*)malloc(sizeof(t_rms_on_pth));
		tmp->rm_path = room_on_path;
		tmp->next = el->ways->rms_on_path;
		el->ways->rms_on_path = tmp;
	}
	else
	{
		tmp = (t_rms_on_pth*)malloc(sizeof(t_rms_on_pth));
		tmp->rm_path = room_on_path;
		tmp->next = NULL;
		el->ways->rms_on_path = tmp;
	}
	
}

void		ways(t_lemin *el)
{
	t_rooms		*tmp;

	el->ways = (t_ways*)malloc(sizeof(t_ways));
	el->ways->next = NULL;
	tmp = el->rms;
	while (tmp->index != el->end)
		tmp = tmp->next;
	// while (tmp->links) // пока есть комнаты-связи у end
	// {
		// ways_add(el)
		while (tmp->links->link != NULL && tmp->links->link->lvl != 0) // пока lvl комнаты-связи1 не равен нулю
		{
			path_add(el, tmp->links->link); // ***сохраняем комнату-связь1
			tmp->links->link->busy = 0; // ставим комнате-связе "занято"
			while (tmp->links->link->links) // пока у комнаты-связи1 есть комнаты-связи2
			{
				if (tmp->links->link->lvl - tmp->links->link->links->link->lvl == 1 &&
					tmp->links->link->links->link->busy == 1) // если разница между lvl комнатами-связями равна 1 && комната "свободна"
					break ;
				tmp->links->link->links = tmp->links->link->links->next;
			}
			tmp->links->link = tmp->links->link->links->link; // присваиваем комнате-связе1 = подходящую комнату-связь2(передвигаемся по пути)
		}
	// 	tmp->links = tmp->links->next; // передвигаемся по комнатам-связям end
	// }
	/*
	** print
	*/
	while (el->ways->rms_on_path)
	{
		ft_printf("path = %s\n", el->ways->rms_on_path->rm_path->room);
		el->ways->rms_on_path = el->ways->rms_on_path->next;
	}
}

void		resave_links(t_lemin *el)
{
	t_rooms     *tmp;

	tmp = el->rms;
	while (tmp && (tmp->links = tmp->first_link) == tmp->first_link)
	{
		tmp = tmp->next;
	}
}

void		lvls(t_lemin *el)
{
    t_rooms     *tmp;
    int         i;
    int         k;

	resave_links(el);
    tmp = el->rms;
    i = 0;
    while (tmp->index != el->start)
		tmp = tmp->next;
    tmp->lvl = 0;
    tmp->busy = 1;
    k = 1;
	while(k > 0 && (tmp = el->rms) == el->rms)
	{
		// tmp = el->rms;
		while (tmp)
		{
			if (tmp->lvl == i)
				while (tmp->first_link)
				{
					if (tmp->first_link->link->busy != 1)
					{
						tmp->first_link->link->lvl = i + 1;
							tmp->first_link->link->busy = 1;
						k++;
					}
					tmp->first_link = tmp->first_link->next;
				}
				tmp = tmp->next;
		}
		++i;
		k = k == 1 ? -1 : 1;
	}
    /*
    ** print
    */
	tmp = el->rms;
	while (tmp)
	{
		ft_printf("room - %s lvl - %d\n", tmp->room, tmp->lvl);
		tmp = tmp->next;
	}
	ways(el);
}