/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 12:42:12 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/01 19:10:36 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		link_save(t_rooms *rm1, t_rooms *ln1)
{
	if (rm1->links)
	{
		while (rm1->links != NULL)
			rm1->links = rm1->links->next;
		rm1->links = (struct s_rel*)malloc(sizeof(struct s_rel));
		rm1->links->link = ln1;
	}
	else
	{
		rm1->links = (struct s_rel*)malloc(sizeof(struct s_rel));
		rm1->links->link = ln1;
		rm1->first_link = rm1->links;
	}
	if (ln1->links)
	{
		while (ln1->links != NULL)
			ln1->links = ln1->links->next;
		ln1->links = (struct s_rel*)malloc(sizeof(struct s_rel));
		ln1->links->link = rm1;
	}
	else
	{
		ln1->links = (struct s_rel*)malloc(sizeof(struct s_rel));
		ln1->links->link = rm1;
		ln1->first_link = ln1->links;
	}
	
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
	list->first_link = NULL;
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
	while (get_next_line(fd, &line) == 1)
	{
		line[0] != '#' ? link_find(line, tmp, tmp) : 0;
		free(line);
	}
	tmp = el->rms;
	while (tmp != NULL)
	{
		// ft_printf("r00ms = %s\n", tmp->room);
		if (tmp->links != NULL)
		{
			while (tmp->first_link->link != NULL)
			{
				ft_printf("l1nks = %s-%s\n", tmp->room, tmp->first_link->link->room);
				tmp->first_link->link = tmp->first_link->link->next;
			}
		}
		tmp = tmp->next;
	}
	// system("leaks lem-in");
	return (0);
}