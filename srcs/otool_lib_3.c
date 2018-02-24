/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_lib_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:33:23 by jtranchi          #+#    #+#             */
/*   Updated: 2018/02/21 14:33:24 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/otool.h"

void		ft_find_fat_32(void *ptr)
{
	int					i;
	int					narch;
	struct fat_header	*fat;
	struct fat_arch		*arch;

	i = -1;
	fat = (struct fat_header*)ptr;
	narch = OSSwapBigToHostInt(fat->nfat_arch);
	arch = (struct fat_arch*)(fat + 1);
	while (++i < (int)narch)
	{
		if (OSSwapBigToHostInt(arch->cputype) == CPU_TYPE_X86_64)
		{
			handle_64(ptr + (((arch->offset & 0xffff0000) >> 16 |
				(arch->offset & 0x0000ffff)) << 8));
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
		if (OSSwapBigToHostInt(arch->cputype) == CPU_TYPE_X86_64)
		{
			handle_64(ptr + (((arch->offset & 0xffff0000) >> 16 |
			(arch->offset & 0x0000ffff)) << 8));
			return ;
		}
		arch = arch + 1;
	}
}
