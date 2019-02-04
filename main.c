/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 12:42:12 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/04 19:01:14 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		link_save(t_rooms *rm1, t_rooms *ln1)
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
}

void		link_find(char	*l, t_rooms *tmp, t_rooms *start)
{
	char	**str;

	str = ft_strsplit(l, '-');
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
		{
			link_save(tmp, start);
		}
	}
	free(str[0]);
	free(str[1]);
	free(str);
}

void		room_add(t_rooms **tmp, char **r, t_lemin *el)
{
	t_rooms	*list;

	list = (t_rooms*)malloc(sizeof(t_rooms));
	list->name = ft_strdup(r[0]);
	list->next = NULL;
	list->links = NULL;
	list->lvl = -1;
	list->busy = -1;
	list->xy[0] = ft_atoi(r[1]);
	list->xy[1] = ft_atoi(r[2]);
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
}

int			room_save(t_rooms **tmp, t_lemin *el, char *l)
{
	char	**str;

	if ((ft_strchr(l, '-')) == 0)
	{
		if (l[1] == '#')
		{
			if ((ft_strcmp(l, "##start")) == 0)
				el->start = *tmp != NULL ? (*tmp)->index + 1 : 0;
			else if ((ft_strcmp(l, "##end")) == 0)
				el->end = *tmp != NULL ? (*tmp)->index + 1 : 0;
		}
		else if (l[0] != '#')
		{
			if ((ft_strchr(l, ' ') != 0))
			{
				str = ft_strsplit(l, ' ');
				room_add(tmp, str, el);
				free(str[0]);
				free(str[1]);
				free(str[2]);
				free(str);
			}
		}
		return (1);
	}
	return (0);
}

int			main(void)
{
	int		fd;
	t_rooms	*tmp;
	t_lemin	*el;
	char	*line;

	el = (t_lemin*)malloc(sizeof(t_lemin));
	el->ways = NULL;
	tmp = NULL;
	fd = open("f1", O_RDWR);
	get_next_line(fd, &line);
	el->ants = ft_atoi(line);
	if (el->ants <= 0)
		return (0);
	free(line);
	while (get_next_line(fd, &line) == 1)
	{
		if (room_save(&tmp, el, line) == 1)
			;
		else if (line[0] != '#')
			link_find(line, el->rms, el->rms);
		free(line);
	}
	// while (el->rms)
	// {
	// 	ft_printf("room %s\n", el->rms->name);
	// 	while (el->rms->links)
	// 	{
	// 		ft_printf("room = %s links = %s\n", el->rms->name, el->rms->links->room->name);
	// 		el->rms->links = el->rms->links->next;
	// 	}
	// 	el->rms = el->rms->next;
	// }
	lvls(el, el->rms, 1, 0);
	// system("leaks -q lem-in");
	return (0);
}