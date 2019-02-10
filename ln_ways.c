/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ln_ways.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 12:58:42 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/10 14:47:40 by seshevch         ###   ########.fr       */
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
	new_path->numb_ant = 0;
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

t_rooms		*find_min_links(t_rooms *end)
{
	t_links		*links;
	t_rooms		*room_min_lvl;

	room_min_lvl = NULL;
	links = end->links;
	while (links)
	{
		if ((room_min_lvl == NULL || links->room->lvl < room_min_lvl->lvl) &&
			links->room->busy == 1)
			room_min_lvl = links->room;
		links = links->next;
	}
	return (room_min_lvl);
}

void		add_way(t_lemin *el, t_ways *tmp)
{
	t_ways	*new_way;

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

void		dell_way(t_ways *tmp)
{
	t_path	*path;

	while (tmp->next->next)
		tmp = tmp->next;
	while (tmp->next->path)
	{
		path = tmp->next->path->next;
		free(tmp->next->path);
		tmp->next->path = path;
	}
	free(tmp->next->path);
	free(tmp->next);
	tmp->next = NULL;
}

void		ways(t_lemin *el, t_rooms *end, t_rooms *r_min_lvl)
{
	t_rooms		*tmp;

	while (end->index != el->end)
		end = end->next;
	while ((tmp = find_min_links(end)) != NULL)
	{
		add_way(el, el->ways);
		path_add(el, end);
		while (tmp != NULL && tmp->lvl != 0)
		{
			path_add(el, tmp);
			tmp->busy = 0;
			r_min_lvl = find_min_links(tmp);
			if (r_min_lvl != NULL)
				tmp = r_min_lvl;
			else
			{
				dell_way(el->ways);
				break ;
			}
		}
		tmp && tmp->lvl == 0 ? path_add(el, tmp) : 0;
		if (el->ways->length == 0)
			break ;
	}
}
