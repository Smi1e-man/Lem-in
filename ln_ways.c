/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ln_ways.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 12:58:42 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/05 17:18:21 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		path_add(t_lemin *el, t_rooms *room_on_path)
{
	t_path			*new_path;
	t_ways			*tmp;

	new_path = (t_path*)malloc(sizeof(t_path));
	new_path->room = room_on_path;
	new_path->busy = 0;
	new_path->next = NULL;
	tmp = el->ways;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp->path)
		new_path->next = tmp->path;
	else
		new_path->next = NULL;
	tmp->path = new_path;
	tmp->length += 1;
}

t_rooms		*find_min_links(t_rooms *end, t_rooms *tmp)
{
	int			lvl;
	int			index;
	t_links		*links;

	lvl = -1;
	index = -1;
	links = end->links;
	while (links)
	{
		if ((lvl == -1 || links->room->lvl < lvl) && links->room->busy == 1)
		{
			index = links->room->index;
			lvl = links->room->lvl;
		}
		links = links->next;
	}
	while (tmp && tmp->index != index)
		tmp = tmp->next;
	return (tmp);
}

void		dell_n_add_way(t_ways *new_way, t_ways *tmp, t_lemin *el, int v)
{
	if (v == 1)
	{
		new_way = (t_ways*)malloc(sizeof(t_ways));
		new_way->path = NULL;
		new_way->length = -2;
		new_way->ants = 0;
		new_way->a_on_th = 0;
		new_way->next = NULL;
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (el->ways)
			tmp->next = new_way;
		else
			el->ways = new_way;	
	}
	else
	{
		while(tmp->next->next)
			tmp = tmp->next;
		tmp->next = NULL;
	}
}

void		ways(t_lemin *el, t_rooms *end)
{
	t_rooms		*tmp;

	while (end->index != el->end)
		end = end->next;
	while ((tmp = find_min_links(end, el->rms)) != NULL)
	{
		dell_n_add_way(NULL, el->ways, el, 1);
		path_add(el, end);
		while (tmp != NULL && tmp->lvl != 0)
		{
			path_add(el, tmp);
			tmp->busy = 0;
			while (tmp->links)
			{
				if (tmp->lvl - tmp->links->room->lvl == 1 &&
					tmp->links->room->busy == 1)
					break ;
				tmp->links = tmp->links->next;
			}
			if (tmp->links != NULL)
				tmp = tmp->links->room;
			else
			{
				dell_n_add_way(NULL, el->ways, el, 0);
				break ;
			}
		}
		if (tmp && tmp->lvl == 0)
			path_add(el, tmp);
	}
}


void		lvls(t_lemin *el, t_rooms *tmp, int k, int i)
{
	t_links		*links;

    while (tmp->index != el->start)
		tmp = tmp->next;
    tmp->lvl = 0;
    tmp->busy = 1;
	while(k > 0 && (tmp = el->rms) == el->rms)
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
	ways(el, el->rms);
	ways_ants(el);
    /*
    ** print
    
	tmp = el->rms;
	while (tmp)
	{
		ft_printf("room - %s lvl - %d\n", tmp->name, tmp->lvl);
		tmp = tmp->next;
	}
	
	while(el->ways)
	{
		ft_printf("\nlength = %d\n", el->ways->length);
		ft_printf("Ants = %d\n", el->ways->ants);
		while (el->ways->path)
		{
			ft_printf("room = %s\n", el->ways->path->room->name);
			el->ways->path = el->ways->path->next;
		}
		el->ways = el->ways->next;
	}
	*/
}