/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 12:42:12 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/01 13:54:12 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		link_save(t_rooms *room, t_rooms *link)
{
	if (room->links)
		while (room->links != NULL)
			room->links = room->links->next;
	if (link->links)
		while (link->links != NULL)
			link->links = link->links->next;
	room->links = (struct s_rel*)malloc(sizeof(struct s_rel));
	link->links = (struct s_rel*)malloc(sizeof(struct s_rel));
	room->links->link = link;
	link->links->link = room;
}

void		link_find(char	*l, t_rooms *tmp, t_rooms *start)
{
	while (tmp)
	{
		if (ft_strcmp(ft_strsub(l, 0, ft_strchr(l, '-') - l), tmp->room) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp != NULL)
	{
		while (start)
		{
			if (ft_strcmp(ft_strsub(l, ft_strchr(l, '-') - l + 1, ft_strlen(l)),
			start->room) == 0)
				break ;
			start = start->next;
		}
		if (start != NULL)
			link_save(tmp, start);
	}
}

void		listnew(t_rooms **tmp, char *r, t_lemin *el)
{
	t_rooms	*list;

	list = (t_rooms*)malloc(sizeof(t_rooms));
	list->room = ft_strdup(r);
	list->next = NULL;
	list->links = NULL;
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

char		*room_save(t_rooms **tmp, t_lemin *el, char *l, int fd)
{
	get_next_line(fd, &l);
	while ((ft_strchr(l, '-')) == 0)
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
				listnew(tmp, ft_strsub(l, 0, ft_strchr(l, ' ') - l), el);
		}
		free(l);
		get_next_line(fd, &l);
	}
	(*tmp)->next = NULL;
	// system("leaks lem-in");

	return (l);
}

int			main(void)
{
	int		fd;
	t_rooms	*tmp;
	t_lemin	*el;
	char	*line;

	el = (t_lemin*)malloc(sizeof(t_lemin));
	tmp = NULL;
	fd = open("f2", O_RDWR);
	get_next_line(fd, &line);
	el->ants = ft_atoi(line);
	if (el->ants <= 0)
		return (0);
	free(line);
	line = room_save(&tmp, el, line, fd);
	// free(tmp);
	tmp = el->rms;
	link_find(line, tmp, tmp);
	// printf("%lu,/n %lu,/n %lu,/n", sizeof(t_lemin), sizeof(t_rooms), sizeof(struct s_rel));
	// free(line);
	// while (get_next_line(fd, &line) == 1)
	// {
	// 	line[0] != '#' ? link_find(line, tmp, tmp) : 0;
	// 	free(line);
	// }
	// tmp = el->rms;
	// while (tmp != NULL)
	// {
	// 	ft_printf("r00ms = %s\n", tmp->room);
	// 	if (tmp->links != NULL)
	// 	{
	// 		while (tmp->links != NULL)
	// 		{
	// 			ft_printf("l1nks = %s-%s\n", tmp->room, tmp->links->link->room);
	// 			tmp->links = tmp->links->next;
	// 		}
	// 	}
	// 	tmp = tmp->next;
	// }
	// system("leaks lem-in");
	return (0);
}