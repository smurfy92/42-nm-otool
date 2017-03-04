/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:50:55 by jtranchi          #+#    #+#             */
/*   Updated: 2017/03/04 17:00:36 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nmotool.h"

static size_t		ft_nbrlen(unsigned long long n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

static	void		ft_print_addr(unsigned long long n)
{
	char				str[ft_nbrlen(n)];
	size_t				len;

	len = ft_nbrlen(n) - 1;
	if (n == 0)
	{
		ft_putstr("                 ");
		return ;
		str[len] = '0';
	}
	str[len + 1] = '\0';
	while (n)
	{
		str[len] = (16 > 10 && n % 16 > 9) ?
			(n % 16) + ('a' - 10) : (n % 16) + 48;
		n /= 16;
		len--;
	}
	ft_putstr("0000000");
	ft_putstr(str);
}

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

static	void		add_list(t_lt **lt, unsigned long long value, char *str)
{
	t_lt *new;
	t_lt *tmp;

	tmp = *lt;
	new = (t_lt*)malloc(sizeof(t_lt));
	new->value = value;
	new->str = strdup(str);
	new->next = NULL;
	if (!*lt)
		*lt = new;
	else
		add_list_next(lt, tmp, new);
}

void				print_output(struct symtab_command *sym, void *ptr)
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
		add_list(&lt, array[i].n_value, stringtable + array[i].n_un.n_strx);
	while (lt)
	{
		ft_print_addr(lt->value);
		ft_putendl(lt->str);
		lt = lt->next;
	}
}
