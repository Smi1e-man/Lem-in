/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ln_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:55:21 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/11 13:20:49 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_error(void)
{
	ft_printf("ERROR\n");
	exit(1);
}

void	ft_prnt_n_join(t_lemin *el, char *part, int	v)
{
	if (!el->prnt && v == 0)
	{
		el->prnt = (t_prnt*)malloc(sizeof(t_prnt));
		el->prnt->str = ft_strdup(part);
		el->prnt->next = NULL;
		el->end_prnt = el->prnt;
	}
	else if (v == 0)
	{
		el->end_prnt->next = (t_prnt*)malloc(sizeof(t_prnt));
		el->end_prnt->next->str = ft_strdup(part);
		el->end_prnt = el->end_prnt->next;
		el->end_prnt->next = NULL;
	}
	if (v == 1)
	{
		el->end_prnt = el->prnt;
		while (el->prnt)
		{
			ft_printf("%s\n", el->prnt->str);
			el->prnt = el->prnt->next;
		}
	}
}

int		ft_numbs(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] < 48 || str[i] > 57)
			return (0);
	return (1);
}

void	validate_room(char *line, char **str, t_rooms *tmp)
{
	int		i;
	int		error;
	int		k;

	i = -1;
	error = 0;
	k = 0;
	while (line[++i])
		if (line[i] == ' ' || line[i] == '\t')
			k++;
	k > 2 || k < 2 ? ft_error() : 0;
	str[0][0] == 'L' ? ft_error() : 0;
	i = 0;
	while (str[++i])
		if (ft_numbs(str[i]) == 0)
			ft_error();
	i > 3 || i < 3 ? ft_error() : 0;
	while (tmp)
	{
		ft_strcmp(str[0], tmp->name) == 0 ? ft_error() : 0;
		tmp = tmp->next;
	}
}

void	validate_link(char **str, t_rooms *room_head)
{
	int		i;
	int		start;
	int		end;
	t_rooms	*tmp;

	start = 0;
	end = 0;
	!str[0] || !str[1] || ft_strcmp(str[0], str[1]) == 0 ? ft_error() : 0;
	i = -1;
	while (str[++i] && (tmp = room_head) == room_head)
	{
		while (tmp)
		{
			if (ft_strcmp(str[i], tmp->name) == 0)
				break ;
			tmp = tmp->next;
		}
		!tmp ? ft_error() : 0;
	}
}
