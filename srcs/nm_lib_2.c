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

int					myerror(char *str)
{
	ft_putstr("./ft_nm: ");
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
		ft_putstr("        ");
		(boo) ? (ft_putstr("        ")) : 0;
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
	(boo) ? (ft_putstr("0000000")) : (ft_putstr("0000"));
	ft_putstr(str);
}

int					print_usage(char **argv)
{
	ft_putstr_fd("usage : ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putendl_fd(" [file]", 2);
	return (EXIT_FAILURE);
}

void				ft_print_letter(t_lt *lt)
{
	char				c;

	c = '?';
	if ((lt->type & N_TYPE) == N_UNDF)
		c = 'U';
	else if ((lt->type & N_TYPE) == N_ABS)
		c = 'A';
	else if ((lt->type & N_TYPE) == N_SECT)
		if (lt->sect == 8)
			c = 'D';
		else
			c = 'T';
	else if ((lt->type & N_TYPE) == N_PBUD)
		c = 'U';
	else if ((lt->type & N_TYPE) == N_INDR)
		c = 'I';
	if ((lt->type & N_STAB) != 0)
		c = 'Z';
	if ((lt->type & N_EXT) == 0 && c != '?')
		c += 32;
	ft_putchar(' ');
	ft_putchar(c);
	ft_putchar(' ');
}
