/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 14:09:02 by jtranchi          #+#    #+#             */
/*   Updated: 2017/07/31 15:35:41 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/otool.h"

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

void		ft_print_addr(unsigned long long n)
{
	char				str[ft_nbrlen(n)];
	size_t				len;

	len = ft_nbrlen(n) - 1;
	if (n == 0)
	{
		ft_putstr("                ");
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

// static	void		add_list_next(t_lt **lt, t_lt *tmp, t_lt *new)
// {
// 	if (ft_strcmp(tmp->str, new->str) > 0)
// 	{
// 		new->next = tmp;
// 		*lt = new;
// 		return ;
// 	}
// 	while (tmp)
// 	{
// 		if (!tmp->next)
// 		{
// 			tmp->next = new;
// 			break ;
// 		}
// 		if (ft_strcmp(tmp->next->str, new->str) > 0)
// 		{
// 			new->next = tmp->next;
// 			tmp->next = new;
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// }

// static	void		add_list(t_lt **lt, unsigned long long value, char *str, uint8_t type)
// {
// 	t_lt *new;
// 	t_lt *tmp;

// 	tmp = *lt;
// 	new = (t_lt*)malloc(sizeof(t_lt));
// 	new->value = value;
// 	new->type = type;
// 	new->str = strdup(str);
// 	new->next = NULL;
// 	if (!*lt)
// 		*lt = new;
// 	else
// 		add_list_next(lt, tmp, new);
// }

void				print_output(struct segment_command *sym, void *ptr)
{
	//int					i;
	//char				*stringtable;
	//struct nlist_64		*array;
	//t_lt				*lt;
	struct section_64 *section;
	size_t offset = 0;

	ptr = (void*)ptr;

	section = (struct section_64 *)(sym + 1);
	printf("\n%llu\n", section->size);
	while (section->offset + offset != section->offset + section->size){
		ft_print_addr(section->offset + offset);
		ft_putstr("\n");
		offset += 16;
	}

	// lt = NULL;
	// stringtable = (void*)ptr + sym->stroff;
	// array = (void*)ptr + sym->symoff;
	// i = -1;
	// while (++i < (int)sym->nsyms)
	// 	add_list(&lt, array[i].n_value, stringtable + array[i].n_un.n_strx, array[i].n_type);
	// while (lt)
	// {
	// 	ft_print_addr(lt->value);
	// 	if (lt->type == N_TYPE)
	// 		ft_putstr(" t ");
	// 	else if (lt->type == N_EXT)
	// 		ft_putstr(" U ");
	// 	else
	// 		ft_putstr(" T ");
		
	// 	ft_putendl(lt->str);
	// 	lt = lt->next;
	// }
}