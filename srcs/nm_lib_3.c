/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_lib_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:44:40 by jtranchi          #+#    #+#             */
/*   Updated: 2018/02/20 15:44:41 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

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
			nm(ptr + OSSwapBigToHostInt(arch->offset));
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
			nm(ptr + OSSwapBigToHostInt(arch->offset));
			return ;
		}
		arch = arch + 1;
	}
}
