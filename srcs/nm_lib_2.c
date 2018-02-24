/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 15:05:12 by jtranchi          #+#    #+#             */
/*   Updated: 2018/02/15 15:05:15 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

int					myerror(char *file, char *str)
{
	ft_putstr("./ft_otool: ");
	ft_putstr(file);
	ft_putstr(": ");
	ft_putendl(str);
	return (EXIT_FAILURE);
}

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

void				ft_print_addr(unsigned long long n, int boo)
{
	char				str[ft_nbrlen(n)];
	size_t				len;

	len = ft_nbrlen(n) - 1;
	if (n == 0)
	{
		;
		(boo) ? (ft_putstr("                ")) : ft_putstr("        ");
		return ;
	}
	str[len + 1] = '\0';
	while (n)
	{
		str[len] = (16 > 10 && n % 16 > 9) ?
			(n % 16) + ('a' - 10) : (n % 16) + 48;
		n /= 16;
		len--;
	}
	if (boo)
		ft_putstr("0000000");
	else
		ft_putstr("0000");
	ft_putstr(str);
}

int					print_usage(char **argv)
{
	ft_putstr_fd("usage : ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putendl_fd(" [file]", 2);
	return (EXIT_FAILURE);
}

void				ft_print_letter(t_lt *lt, char **tab)
{
	char			type;
	char			*section_name;

	type = 0;
	type = ((lt->type & N_TYPE) == N_INDR) ? 'I' : type;
	type = (!type && (lt->type & N_TYPE) == N_STAB) ? '-' : type;
	type = (!type && (lt->type & N_TYPE) == N_UNDF
		&& (lt->type & N_EXT) && lt->value != 0) ? 'C' : type;
	type = (!type && (lt->type & N_TYPE) == N_UNDF
		&& (lt->type & N_TYPE) == N_PBUD) ? 'u' : type;
	type = (!type && (lt->type & N_TYPE) == N_UNDF) ? 'U' : type;
	type = (!type && (lt->type & N_TYPE) == N_ABS) ? 'A' : type;

	if (!type && (lt->type & N_TYPE) == N_SECT)
	{
		section_name = tab[lt->sect - 1];
		if (section_name && (!ft_strcmp(section_name, "__text")
			|| !ft_strcmp(section_name, "__data")
			|| !ft_strcmp(section_name, "__bss")))
			type = ft_toupper(section_name[2]);
		else
			type = 'S';
	}

	ft_putchar(' ');
	ft_putchar(!(lt->type & N_EXT) ? ft_tolower(type) : type);
	ft_putchar(' ');
}

