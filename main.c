/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 12:42:12 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/11 13:20:45 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		link_save(t_rooms *rm1, t_rooms *ln1, t_lemin *el)
{
	t_links		*tmp;
	t_links		*pmt;

	tmp = (t_links*)malloc(sizeof(t_links));
	tmp->room = ln1;
	if (rm1->links)
		tmp->next = rm1->links;
	else
		tmp->next = NULL;
	rm1->links = tmp;
	pmt = (t_links*)malloc(sizeof(t_links));
	pmt->room = rm1;
	if (ln1->links)
		pmt->next = ln1->links;
	else
		pmt->next = NULL;
	ln1->links = pmt;
	el->lnk++;
}

void		link_find(t_lemin *el, char *l, t_rooms *tmp, t_rooms *start)
{
	char	**str;

	str = ft_strsplit(l, '-');
	validate_link(str, tmp);
	while (tmp)
	{
		if (ft_strcmp(str[0], tmp->name) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp != NULL)
	{
		while (start)
		{
			if (ft_strcmp(str[1], start->name) == 0)
				break ;
			start = start->next;
		}
		if (start != NULL)
			link_save(tmp, start, el);
		free(str[0]);
		free(str[1]);
		free(str);
	}
}

void		room_add(t_rooms **tmp, char **r, t_lemin *el, t_rooms *list)
{
	list = (t_rooms*)malloc(sizeof(t_rooms));
	list->name = ft_strdup(r[0]);
	list->next = NULL;
	list->links = NULL;
	list->lvl = -1;
	list->busy = -1;
	if ((*tmp))
	{
		list->index = (*tmp)->index + 1;
		(*tmp)->next = list;
		*tmp = (*tmp)->next;
	}
	else
	{
		list->index = 0;
		*tmp = list;
		el->rms = *tmp;
	}
	if ((*tmp)->index == el->start)
	{
		el->str = *tmp;
		el->str->busy = 1;
		el->str->lvl = 0;
	}
	el->end_str = (*tmp)->index == el->end ? *tmp : 0;
}

int			room_save(t_rooms **tmp, t_lemin *el, char *l)
{
	if ((ft_strchr(l, '-')) == 0)
	{
		if (l[1] == '#')
		{
			if ((ft_strcmp(l, "##start")) == 0)
			{
				el->start != -1 ? ft_error() : 0;
				el->start = *tmp != NULL ? (*tmp)->index + 1 : 0;
			}
			else if ((ft_strcmp(l, "##end")) == 0)
			{
				el->end != -1 ? ft_error() : 0;
				el->end = *tmp != NULL ? (*tmp)->index + 1 : 0;
			}
		}
		else if (l[0] != '#')
			room_link(tmp, el, l);
		return (1);
	}
	el->start == -1 || el->end == -1 || el->start == el->end ? ft_error() : 0;
	return (0);
}

int			main(void)
{
	t_rooms	*tmp;
	t_lemin	*el;
	char	*line;

	el = (t_lemin*)malloc(sizeof(t_lemin));
	nul_struct(el);
	tmp = NULL;
	get_next_line(0, &line);
	!line || line[0] == '\0' || ft_numbs(line) == 0 ? ft_error() : 0;
	el->ants = ft_atoi(line);
	ft_prnt_n_join(el, line, 0);
	free(line);
	while (get_next_line(0, &line) == 1)
	{
		ft_prnt_n_join(el, line, 0);
		if (room_save(&tmp, el, line) == 1)
			;
		else if (line[0] != '#')
			link_find(el, line, el->rms, el->rms);
		free(line);
	}
	el->start == -1 || el->end == -1 || el->start == el->end ? ft_error() : 0;
	!el->str || !el->end || el->lnk == 0 || el->ants <= 0 ? ft_error() : 0;
	lvls(el, el->str, 1, 0);
	return (0);
}
