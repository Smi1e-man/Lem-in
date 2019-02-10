/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ln_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:55:21 by seshevch          #+#    #+#             */
/*   Updated: 2019/02/10 14:22:05 by seshevch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_error(void)
{
	ft_printf("ERROR\n");
	exit(1);
}

void	ft_prnt_n_join(t_lemin *el, char *part)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin(el->prnt, "\n");
	s2 = ft_strjoin(s1, part);
	free(s1);
	free(el->prnt);
	el->prnt = s2;
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
	t_rooms	*tmp;

	ft_strcmp(str[0], str[1]) == 0 ? ft_error() : 0;
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
	i > 2 || i < 2 ? ft_error() : 0;
}
