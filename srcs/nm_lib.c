/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:50:55 by jtranchi          #+#    #+#             */
/*   Updated: 2017/07/31 12:09:25 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

static	void		add_list_next(t_lt **lt, t_lt *tmp, t_lt *new)
{
	if (ft_strcmp(tmp->str, new->str) > 0)
	{
		new->next = tmp;
		*lt = new;
		return ;
	}
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
		tmp = tmp->next;
	}
}

static	void		add_list_64(t_lt **lt, unsigned long long value,
char *str, struct nlist_64 array)
{
	t_lt *new;
	t_lt *tmp;

	tmp = *lt;
	new = (t_lt*)malloc(sizeof(t_lt));
	new->value = value;
	new->type = array.n_type;
	new->sect = array.n_sect;
	new->str = ft_strdup(str);
	new->next = NULL;
	if (!*lt)
		*lt = new;
	else
		add_list_next(lt, tmp, new);
}

static	void		add_list_32(t_lt **lt, unsigned long long value,
char *str, struct nlist array)
{
	t_lt *new;
	t_lt *tmp;

	tmp = *lt;
	new = (t_lt*)malloc(sizeof(t_lt));
	new->value = value;
	new->type = array.n_type;
	new->sect = array.n_sect;
	new->str = ft_strdup(str);
	new->next = NULL;
	if (!*lt)
		*lt = new;
	else
		add_list_next(lt, tmp, new);
}

void				print_output_64(struct symtab_command *sym, void *ptr)
{
	int					i;
	char				*stringtable;
	struct nlist_64		*array;
	t_lt				*lt;

	lt = NULL;
	stringtable = (void*)ptr + sym->stroff;
	array = (void*)ptr + sym->symoff;
	i = -1;
	while (++i < (int)sym->nsyms)
		add_list_64(&lt, array[i].n_value, stringtable +
		array[i].n_un.n_strx, array[i]);
	while (lt)
	{
		ft_print_addr(lt->value, 1);
		ft_print_letter(lt);
		ft_putendl(lt->str);
		lt = lt->next;
	}
}

void				print_output_32(struct symtab_command *sym, void *ptr)
{
	int					i;
	char				*stringtable;
	struct nlist		*array;
	t_lt				*lt;

	lt = NULL;
	stringtable = (void*)ptr + sym->stroff;
	array = (void*)ptr + sym->symoff;
	i = -1;
	while (++i < (int)sym->nsyms)
		add_list_32(&lt, array[i].n_value, stringtable +
		array[i].n_un.n_strx, array[i]);
	while (lt)
	{
		ft_print_addr(lt->value, 0);
		ft_print_letter(lt);
		ft_putendl(lt->str);
		lt = lt->next;
	}
}
