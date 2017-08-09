/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 14:09:02 by jtranchi          #+#    #+#             */
/*   Updated: 2017/08/09 17:02:52 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/otool.h"

void	print_byte_to_hex(char byte)
{
	char			str[2];
	short			count;
	short			char_hex;
	unsigned char	cast;

	cast = (unsigned char)byte;
	count = -1;
	while (++count != 2)
	{
		char_hex = cast % 16;
		cast /= 16;
		if (char_hex < 10)
			str[count] = char_hex + '0';
		else
			str[count] = (char_hex % 10) + 'a';
	}
	ft_putchar(str[1]);
	ft_putchar(str[0]);
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
	ft_putstr("0000000100000");
	ft_putstr(str);
}

void				print_output(struct segment_command_64 *seg,
struct mach_header_64 *header)
{
	struct section_64	*section;
	size_t				offset = 0;
	size_t				count = 0;

	section = (struct section_64 *)(seg + 1);
	while (count < seg->nsects) {
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
			break;
		section += 1;
		count ++;
	}
	while ((char *)header + section->offset + offset < 
		(char *)header + section->offset + section->size){
		ft_print_addr(section->offset + offset);
		count = -1;
		while (++count < 16) {
			ft_putchar(' ');
			print_byte_to_hex(*((char *)header + section->offset + offset++));
			if ((char *)header + section->offset + offset < 
			(char *)header + section->offset + section->size)
				break;
		}
		ft_putstr("\n");
	}
}