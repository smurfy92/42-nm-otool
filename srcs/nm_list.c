/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:50:55 by jtranchi          #+#    #+#             */
/*   Updated: 2018/02/26 22:09:04 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

static void		push_list(t_lt **lt, t_lt *tmp, t_lt *new)
{
	if (ft_strcmp(tmp->str, new->str) > 0)
	{
		new->next = tmp;
		*lt = new;
		return ;
	}
	if (ft_strcmp(tmp->str, new->str) == 0)
	{
		if (tmp->value > new->value)
		{
			new->next = tmp;
			*lt = new;
			return ;
		}
	}
	push_list_next(tmp, new);
}

static void		add_list_64(t_lt **lt, char *str, struct nlist_64 array)
{
	t_lt *new;
	t_lt *tmp;

	tmp = *lt;
	new = (t_lt*)malloc(sizeof(t_lt));
	new->value = array.n_value;
	new->type = array.n_type;
	new->sect = array.n_sect;
	new->str = str;
	new->next = NULL;
	if (!*lt)
		*lt = new;
	else
		push_list(lt, tmp, new);
}

static void		add_list_32(t_lt **lt, char *str, struct nlist array)
{
	t_lt *new;
	t_lt *tmp;

	tmp = *lt;
	new = (t_lt*)malloc(sizeof(t_lt));
	new->value = array.n_value;
	new->type = array.n_type;
	new->sect = array.n_sect;
	new->str = str;
	new->next = NULL;
	if (!*lt)
		*lt = new;
	else
		push_list(lt, tmp, new);
}

void			print_output_64(struct symtab_command *sym, void *ptr,
char **tab)
{
	uint32_t			i;
	char				*stringtable;
	struct nlist_64		*array;
	t_lt				*lt;
	t_lt				*tmp;

	lt = NULL;
	stringtable = (void*)ptr + sym->stroff;
	array = (void*)ptr + sym->symoff;
	i = -1;
	while (++i < sym->nsyms)
		if (!(array[i].n_type & N_STAB))
			add_list_64(&lt, stringtable + array[i].n_un.n_strx, array[i]);
	while (lt)
	{
		if (lt->value == 0 && (lt->type & N_TYPE) != N_UNDF)
			ft_putstr("0000000000000000");
		else
			ft_print_addr(lt->value, 1);
		ft_print_letter(lt, tab);
		ft_putendl(lt->str);
		tmp = lt->next;
		free(lt);
		lt = tmp;
	}
	free(tab);
}

void			print_output_32(struct symtab_command *sym, void *ptr,
char **tab)
{
	uint32_t			i;
	char				*stringtable;
	struct nlist		*array;
	t_lt				*lt;
	t_lt				*tmp;

	lt = NULL;
	stringtable = (void*)ptr + sym->stroff;
	array = (void*)ptr + sym->symoff;
	i = -1;
	while (++i < sym->nsyms)
		if (!(array[i].n_type & N_STAB))
			add_list_32(&lt, stringtable + array[i].n_un.n_strx, array[i]);
	while (lt)
	{
		if (lt->value == 0 && (lt->type & N_TYPE) != N_UNDF)
			ft_putstr("00000000");
		else
			ft_print_addr(lt->value, 0);
		ft_print_letter(lt, tab);
		ft_putendl(lt->str);
		tmp = lt->next;
		free(lt);
		lt = tmp;
	}
	free(tab);
}
