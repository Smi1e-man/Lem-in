/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 12:42:12 by seshevch          #+#    #+#             */
/*   Updated: 2019/01/28 20:01:46 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_rooms		*ft_listnew(t_rooms *el, char *r)
{
	t_rooms	*list;

	list = (t_rooms*)malloc(sizeof(t_rooms));
	el->room = ft_strdup(r);
	list->index = el->index + 1;
	el->next = list;
	return (list);
}

char		*room_save(t_rooms **tmp, t_lemin *el, char *l, int fd)
{
	get_next_line(fd, &l);
	while ((ft_strchr(l, '-')) == 0)
	{
		if (l[1] == '#')
		{
			if ((ft_strcmp(l, "##start")) == 0)
				el->start = (*tmp)->index;
			else if ((ft_strcmp(l, "##end")) == 0)
				el->end = (*tmp)->index;
		}
		else if (l[0] != '#')
		{
			if ((ft_strchr(l, ' ') != 0))
				*tmp = ft_listnew(*tmp, ft_strsub(l, 0, ft_strchr(l, ' ') - l));
		}
		free(l);
		get_next_line(fd, &l);
	}
	return (l);
}

void		room_in_massive(int size, t_lemin **el)
{
	int		i;

	(*el)->rooms = (char **)malloc(sizeof(char*) * size + 1);
	i = 0;
	while ((*el)->rms->next != NULL)
	{
		(*el)->rooms[i] = (*el)->rms->room;
		i++;
		(*el)->rms = (*el)->rms->next;
	}
	(*el)->rooms[i] = NULL;
	size = i;
	(*el)->links = (char **)malloc(sizeof(char*) * size + 1);
	i = -1;
	while (++i < size)
	{
		(*el)->links[i] = (char*)ft_memset(ft_strnew(size), '0', size);
	}
	(*el)->links[i] = NULL;
}

void		link_save(char *line, t_lemin *el, int i, int numb)
{
	int		index;

	i = -1;
	numb = -1;
	while (el->rooms[++i] != NULL && numb != 0)
		numb = ft_strcmp(ft_strsub(line, 0, ft_strchr(line, '-') - line),
		el->rooms[i]);
	if (numb == 0)
	{
		index = i - 1;
		i = -1;
		numb = -1;
		while (el->rooms[++i] != NULL && numb != 0)
			numb = ft_strcmp(ft_strsub(line, ft_strchr(line, '-') - line + 1,
			ft_strlen(line)), el->rooms[i]);
		if (numb == 0)
		{
			el->links[index][i - 1] = '1';
			el->links[i - 1][index] = '1';
		}
	}
}

int			main(void)
{
	int		fd;
	t_rooms	*tmp;
	t_lemin	*el;
	char	*line;

	el = (t_lemin*)malloc(sizeof(t_lemin));
	el->rms = (t_rooms*)malloc(sizeof(t_rooms));
	el->rms->index = 0;
	tmp = el->rms;
	fd = open("f1", O_RDWR);
	get_next_line(fd, &line);
	el->ants = ft_atoi(line);
	if (el->ants <= 0)
		return (0);
	free(line);
	line = room_save(&tmp, el, line, fd);
	room_in_massive(tmp->index, &el);
	link_save(line, el, -1, -1);
	free(line);
	while (get_next_line(fd, &line) == 1)
	{
		line[0] != '#' ? link_save(line, el, -1, -1) : 0;
		free(line);
	}
	// i = -1;
	// while (++i < tmp->index)
	// {
	// 	ft_printf("r00ms = %s\n", el->rooms[i]);
	// }
	// i = -1;
	// while(el->links[++i] != NULL)
	// {
	// 	ft_printf("%s\n", el->links[i]);
	// }
	return (0);
}