/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 15:32:41 by jtranchi          #+#    #+#             */
/*   Updated: 2017/08/09 16:55:41 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"


char		**get_tab_64(char **tabl, struct segment_command_64 *seg)
{
	int i;
	int y;
	struct section_64 *sec;
	char **tab2;

	i = 0;
	printf("ici\n");
	if ((int)seg->nsects < 1)
		return (tabl);
	printf("ici1.5\n");
	while (tabl && tabl[i])
		i++;
	tab2 = (char**)malloc(sizeof(char*) * (int)seg->nsects + i + 1);
	tab2[(int)seg->nsects + i] = 0;
	i = 0;
	printf("ici2\n");
	while (tabl && tabl[i])
	{
		tab2[i] = tabl[i];
		i++;
	}
	printf("ici3\n");
	sec = (struct section_64 *)((void *)seg + sizeof(struct segment_command_64));
	y = -1;
	while (++y < (int)seg->nsects)
	{
		tab2[i] = sec->sectname;
		i++;
		sec = sec + 1;
	}
	printf("ici4\n");
	return (tab2);
}

char		**get_tab_32(char **tabl, struct segment_command *seg)
{
	int i;
	int y;
	struct section *sec;
	char **tab2;

	i = 0;
	if ((int)seg->nsects < 1)
		return (tabl);
	while (tabl && tabl[i])
		i++;
	tab2 = (char**)malloc(sizeof(char*) * (int)seg->nsects + i + 1);
	tab2[(int)seg->nsects + i] = 0;
	i = 0;
	while (tabl && tabl[i])
	{
		tab2[i] = tabl[i];
		i++;
	}

	sec = (struct section *)((void *)seg + sizeof(struct segment_command));
	y = -1;
	while (++y < (int)seg->nsects)
	{
		tab2[i] = sec->sectname;
		i++;
		sec = sec + 1;
	}

	return (tab2);
}

void		handle_64(void *ptr)
{
	int						nb;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	char **tabl;

	i = -1;
	header = (struct mach_header_64*)ptr;
	nb = header->ncmds;
	lc = (void*)ptr + sizeof(*header);
	tabl = NULL;

	while (++i < nb)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			printf("start\n");
			tabl = get_tab_64(tabl, (struct segment_command_64 *)lc);
			printf("end\n");
		}
		lc = (void*)lc + lc->cmdsize;
	}
	printf("sortie\n");
	i = -1;
	lc = (void*)ptr + sizeof(*header);
	while (++i < nb)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command*)lc;
			printf("print start\n");
			print_output_64(sym, ptr, tabl);
			printf("print end\n");

			break ;
		}
		lc = (void*)lc + lc->cmdsize;
	}
}


void		handle_32(void *ptr)
{
	int						nb;
	int						i;
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	char **tabl;

	i = -1;
	header = (struct mach_header*)ptr;
	nb = header->ncmds;
	lc = (void*)ptr + sizeof(*header);
	tabl = NULL;
	while (++i < nb)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			tabl = get_tab_32(tabl, (struct segment_command*)lc);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	i = -1;
	while (++i < nb)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command*)lc;
			print_output_32(sym, ptr, tabl);
			break ;
		}
		lc = (void*)lc + lc->cmdsize;
	}
}

void		nm(void *ptr)
{
	int magic;

	magic = *(int *)ptr;
	if (magic == (int)MH_MAGIC_64)
		handle_64(ptr);
	else if (magic == (int)MH_MAGIC)
		handle_32(ptr);
	else if (magic == (int)FAT_CIGAM_64)
		ft_find_fat_64(ptr);
	else if (magic == (int)FAT_CIGAM)
		ft_find_fat_32(ptr);
}

void		ft_process(int argc, char *argv)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if (argc > 2)
	{
		ft_putstr(argv);
		ft_putendl(":");
	}
	if ((fd = open(argv, O_RDONLY)) < 0)
		myerror(argv, "Permission or file doesnt exists");
	else if (fstat(fd, &buf) < 0)
		myerror(argv, "fstat");
	else if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
	MAP_FAILED)
		myerror(argv, "mmap");
	else
	{
		nm(ptr);
		if (munmap(ptr, buf.st_size) < 0)
			myerror(argv, "munmap");
	}
}

int			main(int argc, char **argv)
{
	int			i;

	i = 0;
	if (argc < 2)
		return (print_usage(argv));
	while (++i < argc)
		ft_process(argc, argv[i]);
	return (EXIT_SUCCESS);
}
