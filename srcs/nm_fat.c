/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_lib_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 15:05:12 by jtranchi          #+#    #+#             */
/*   Updated: 2018/02/25 02:36:32 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void		ft_print_letter(t_lt *lt, char **tab)
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
		type = (section_name && (!ft_strcmp(section_name, "__text")
			|| !ft_strcmp(section_name, "__data")
			|| !ft_strcmp(section_name, "__bss"))) ?
		ft_toupper(section_name[2]) : 'S';
	}
	ft_putchar(' ');
	ft_putchar(!(lt->type & N_EXT) ? ft_tolower(type) : type);
	ft_putchar(' ');
}

void		ft_find_fat_32(void *ptr)
{
	int					i;
	int					narch;
	struct fat_header	*fat;
	struct fat_arch		*arch;

	i = -1;
	fat = (struct fat_header*)ptr;
	narch = reverse_endian(fat->nfat_arch);
	arch = (struct fat_arch*)(fat + 1);
	while (++i < (int)narch)
	{
		if (reverse_endian(arch->cputype) == CPU_TYPE_X86_64)
		{
			nm(ptr + reverse_endian(arch->offset));
			return ;
		}
		arch = arch + 1;
	}
}

void		ft_find_fat_64(void *ptr)
{
	int					i;
	int					narch;
	struct fat_header	*fat;
	struct fat_arch_64	*arch;

	i = -1;
	fat = (struct fat_header*)ptr;
	narch = OSSwapBigToHostInt(fat->nfat_arch);
	arch = (struct fat_arch_64*)(fat + 1);
	while (++i < (int)narch)
	{
		if (reverse_endian(arch->cputype) == CPU_TYPE_X86_64)
		{
			nm(ptr + reverse_endian(arch->offset));
			return ;
		}
		arch = arch + 1;
	}
}
