/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:55:55 by jtranchi          #+#    #+#             */
/*   Updated: 2018/02/26 17:55:56 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void		push_list_next(t_lt *tmp, t_lt *new)
{
	while (tmp)
	{
		if (!tmp->next)
		{
			tmp->next = new;
			break ;
		}
		if (ft_strcmp(tmp->next->str, new->str) > 0)
		{
			new->next = tmp->next;
			tmp->next = new;
			break ;
		}
		if (ft_strcmp(tmp->next->str, new->str) == 0)
		{
			if (tmp->next->value > new->value)
			{
				new->next = tmp->next;
				tmp->next = new;
				break ;
			}
		}
		tmp = tmp->next;
	}
}

char		**get_tab_64(char **tabl, struct segment_command_64 *seg)
{
	int					i;
	int					y;
	struct section_64	*sec;
	char				**tab2;

	i = 0;
	if ((int)seg->nsects < 1)
		return (tabl);
	while (tabl && tabl[i])
		i++;
	tab2 = (char**)malloc(sizeof(char*) * ((int)seg->nsects + i + 1));
	tab2[seg->nsects + i] = 0;
	i = 0;
	while (tabl && tabl[i])
		(tab2[i] = tabl[i]) ? (i++) : 0;
	sec = (struct section_64*)(seg + 1);
	y = -1;
	while (++y < (int)seg->nsects)
		(tab2[i++] = sec->sectname) ? (sec++) : 0;
	free(tabl);
	return (tab2);
}

char		**get_tab_32(char **tabl, struct segment_command *seg)
{
	int					i;
	int					y;
	struct section		*sec;
	char				**tab2;

	i = 0;
	if ((int)seg->nsects < 1)
		return (tabl);
	while (tabl && tabl[i])
		i++;
	tab2 = (char**)malloc(sizeof(char*) * ((int)seg->nsects + i + 1));
	tab2[seg->nsects + i] = 0;
	i = 0;
	while (tabl && tabl[i])
		(tab2[i] = tabl[i]) ? (i++) : 0;
	sec = (struct section*)(seg + 1);
	y = -1;
	while (++y < (int)seg->nsects)
		(sec++) ? (tab2[i++] = sec->sectname) : 0;
	free(tabl);
	return (tab2);
}
