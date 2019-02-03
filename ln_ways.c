/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ln_ways.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 12:58:42 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/03 18:41:34 by seshevch         ###   ########.fr       */
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
	el->ways->lenth += 1;
}

t_rooms		*find_min_links(t_lemin *el, t_rooms *end)
{
	int		lvl;
	int		index;
	t_rooms	*tmp;

	lvl = -1;
	index = -1;
	tmp = el->rms;
	end->first_link = end->links;
	while (end->first_link)
	{
		if ((lvl == -1 || end->first_link->link->lvl < lvl) &&
		end->first_link->link->busy != 0)
		{
			index = end->first_link->link->index;
			lvl = end->first_link->link->lvl;
		}
		end->first_link = end->first_link->next;
	}
	while (tmp && tmp->index != index)
		tmp = tmp->next;
	return (tmp);
}

void		ways_add(t_lemin *el)
{
	t_ways	*new_way;

	new_way = (t_ways*)malloc(sizeof(t_ways));
	new_way->rms_on_path = NULL;
	if (!el->ways)
	{
		new_way->next = NULL;
		new_way->lenth = 0;
	}
	else
		new_way->next = el->ways;
	el->ways = new_way;
}

void		ways(t_lemin *el)
{
	t_rooms		*tmp;
	t_rooms		*end;
	t_ways	*print;

	// el->ways = (t_ways*)malloc(sizeof(t_ways));
	// el->ways->next = NULL;
	end = el->rms;
	while (end->index != el->end) // находим end
		end = end->next;
	while ((tmp = find_min_links(el, end)) != NULL) // пока есть комнаты-связи у end
	{
		ways_add(el);
		// tmp = find_min_links(end);
		while (tmp != NULL && tmp->lvl != 0) // пока lvl комнаты-связи1 не равен нулю
		{
			path_add(el, tmp); // ***сохраняем комнату-связь1
			// el->ways->lenth += 1;
			tmp->busy = 0; // ставим комнате-связе "занято"
			while (tmp->links) // пока у комнаты-связи1 есть комнаты-связи2
			{
				if (tmp->lvl - tmp->links->link->lvl == 1 &&
					tmp->links->link->busy == 1) // если разница между lvl комнатами-связями равна 1 && комната "свободна"
					break ;
				tmp->links = tmp->links->next;
			}
			if (tmp->links != NULL)
				tmp = tmp->links->link; // присваиваем комнате-связе1 = подходящую комнату-связь2(передвигаемся по пути)
			else
				break ;
		}
	// 	tmp->links = tmp->links->next; // передвигаемся по комнатам-связям end
	}
	/*
	** print
	*/
	print = el->ways;
	t_rms_on_pth *p;
	while (print)
	{
		ft_printf("lenth way = %d\n", print->lenth);
		p = print->rms_on_path;
		while (p)
		{
			ft_printf(" path = %s\n", p->rm_path->room);
			p = p->next;
		}
		print = print->next;
	}
}

void		resave_links(t_lemin *el)
{
	t_rooms     *tmp;

	tmp = el->rms;
	while (tmp && (tmp->links = tmp->first_link) == tmp->first_link)
		tmp = tmp->next;
}

void		lvls(t_lemin *el, t_rooms *tmp, int k, int i)
{
    // t_rooms     *tmp;
    // int         i;
    // int         k;

	resave_links(el);
    tmp = el->rms;
    // i = 0;
    while (tmp->index != el->start)
		tmp = tmp->next;
    tmp->lvl = 0;
    tmp->busy = 1;
    // k = 1;
	while(k > 0 && (tmp = el->rms) == el->rms)
	{
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
	// tmp = el->rms;
	// while (tmp)
	// {
	// 	ft_printf("room - %s lvl - %d\n", tmp->room, tmp->lvl);
	// 	tmp = tmp->next;
	// }
	ways(el);
}