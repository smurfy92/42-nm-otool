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

void				print_output_64_suite(char *header,
struct section_64 *section, int boo)
{
	size_t				offset;
	size_t				count;

	offset = 0;
	while (header + section->offset + offset <
	header + section->offset + section->size)
	{
		ft_print_addr(section->offset + offset, boo);
		count = -1;
		while (++count < 16)
		{
			ft_putchar(' ');
			print_byte_to_hex(*(header + section->offset + offset + count));
			if ((char *)header + section->offset + offset + count + 1 >=
			(char *)header + section->offset + section->size)
				break ;
		}
		offset += 16;
		ft_putstr("\n");
	}
}

void				print_output_32_suite(char *header,
struct section *section, int boo)
{
	size_t				offset;
	size_t				count;

	offset = 0;
	while (header + section->offset + offset <
	header + section->offset + section->size)
	{
		ft_print_addr(section->offset + offset, boo);
		count = -1;
		while (++count < 16)
		{
			ft_putchar(' ');
			print_byte_to_hex(*(header + section->offset + offset + count));
			if ((char *)header + section->offset + offset + count + 1 >=
			(char *)header + section->offset + section->size)
				break ;
		}
		offset += 16;
		ft_putstr("\n");
	}
}

void				print_output_64(struct segment_command_64 *seg,
struct mach_header_64 *header)
{
	struct section_64	*section;
	size_t				count;

	count = -1;
	section = (struct section_64 *)(seg + 1);
	while (++count < seg->nsects)
	{
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
			break ;
		section += 1;
	}
	print_output_64_suite((char *)header, section, 1);
}

void				print_output_32(struct segment_command *seg,
struct mach_header *header)
{
	struct section		*section;
	size_t				count;

	count = -1;
	section = (struct section *)(seg + 1);
	while (++count < seg->nsects)
	{
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
			break ;
		section += 1;
	}
	print_output_32_suite((char *)header, section, 0);
}
