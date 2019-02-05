/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ln_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 08:58:50 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/05 17:33:51 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	first_ant(t_ways *way)
{
	t_path	*path;

	path = way->path;
	while (path)
	{
		if (path->busy == 0)
			break ;
		path = path->next;
	}
	if (path)
	{
		path->busy = 1;
		way->a_on_th += 1;
	}
}

void	go_ant(t_lemin *el, t_ways *way)
{
	t_path	*path;
	int		a_on_th;

	path = way->path;
	a_on_th = way->a_on_th;
	while (a_on_th > 0 && (path = way->path) == way->path)
	{
		while (path && path->busy != 1)
			path = path->next;
		while (path->next && path->busy == 1 && path->next->busy == 1)
			path = path->next;
		path->busy = 0;
		if (path->next->next == NULL)
		{
			el->ants -= 1;
			way->ants -= 1;
			way->a_on_th -= 1;
		}
		else
			path->next->busy = 1;
		a_on_th--;
	}
}

void	push_ants(t_lemin *el)
{
	t_ways	*ways;
	t_path	*path;
	int		i;

	i = 0;
	while (el->ants > 0 && (ways = el->ways) == el->ways)
	{
		while (ways)
		{
			go_ant(el, ways);
			if (ways->a_on_th != ways->ants)
				first_ant(ways);
			ways = ways->next;
		}
		ways = el->ways;
		i++;
		while (ways)
		{
			path = ways->path;
			ft_printf("|step = %d|   ", i);
			while (path)
			{
				if (path->busy == 1)
					ft_printf("Ant in room = %s  ", path->room->name);
				path = path->next;
			}
			ways = ways->next;
		}
		ft_printf("\n\n");
	}
}

void	free_ways(t_lemin *el)
{
	t_ways	*way;

	way = el->ways;
	while (way->next && way->next->ants != 0)
	{
		way->path = way->path->next;
		way = way->next;
	}
	way->path = way->path->next;
	way->next = NULL;
}

void    ways_ants(t_lemin *el)
{
    int     ants;
    t_ways  *ways;

    ants = el->ants;
    while (ants > 0 && (ways = el->ways) == el->ways)
    {
		while (ways)
		{
			if (!ways->next || ((ways->length + 1) <= (ways->next->length + 1)))
				break ;
			ways = ways->next;
		}
		ways->length += 1;
		ways->ants += 1;
		ants--;
	}
	free_ways(el);
	push_ants(el);
}