/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ln_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 08:58:50 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/10 14:31:45 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	first_ant(t_lemin *el, t_ways *way, int ant)
{
	t_path	*path;

	path = way->path;
	if (path)
	{
		if (path->room->index != el->end)
		{
			path->busy = 1;
			path->numb_ant = ant;
			ft_printf("L%d-%s ", path->numb_ant, path->room->name);
			way->a_on_th += 1;
		}
		else
		{
			while (el->ants)
			{
				path->numb_ant = ant++;
				ft_printf("L%d-%s ", path->numb_ant, path->room->name);
				el->ants--;
			}
		}
	}
}

void	go_ant(t_lemin *el, t_ways *way, int a_on_th)
{
	t_path	*path;

	path = way->path;
	while (--a_on_th > 0 && (path = way->path) == way->path &&
			path->room->index != el->end)
	{
		while (path && path->busy != 1)
			path = path->next;
		while (path->next && path->busy == 1 && path->next->busy == 1)
			path = path->next;
		path->busy = 0;
		path->next->numb_ant = path->numb_ant;
		ft_printf("L%d-%s ", path->next->numb_ant, path->next->room->name);
		if (path->next->next == NULL)
		{
			el->ants -= 1;
			way->ants -= 1;
			way->a_on_th -= 1;
		}
		else
			path->next->busy = 1;
	}
}

void	push_ants(t_lemin *el)
{
	t_ways	*ways;
	int		b;
	int		i;

	b = 0;
	i = 1;
	ft_printf("\n\n");
	while (el->ants > 0 && (ways = el->ways) == el->ways)
	{
		b++;
		while (ways)
		{
			go_ant(el, ways, ways->a_on_th + 1);
			if (ways->a_on_th != ways->ants)
			{
				first_ant(el, ways, i);
				i++;
			}
			ways = ways->next;
		}
		ft_printf("\n");
	}
}

void	free_ways(t_lemin *el)
{
	t_ways	*way;
	t_path	*path_head;

	way = el->ways;
	while (way->next && way->next->ants != 0)
	{
		path_head = way->path->next;
		free(way->path);
		way->path = path_head;
		way = way->next;
	}
	path_head = way->path->next;
	free(way->path);
	way->path = path_head;
	while (way->next != NULL)
	{
		dell_way(way);
	}
}

void	ways_ants(t_lemin *el)
{
	int		ants;
	t_ways	*ways;

	ants = el->ants;
	while (ants > 0 && (ways = el->ways) == el->ways)
	{
		while (ways)
		{
			if (!ways->next || ((ways->length) <= (ways->next->length)))
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
