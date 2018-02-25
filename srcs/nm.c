/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 15:32:41 by jtranchi          #+#    #+#             */
/*   Updated: 2018/02/25 02:24:47 by jtranchi         ###   ########.fr       */
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
	if ((int)seg->nsects < 1)
		return (tabl);
	while (tabl && tabl[i])
		i++;
	tab2 = (char**)malloc(sizeof(char*) * ((int)seg->nsects + i + 1));
	tab2[seg->nsects + i] = 0;
	i = 0;
	while (tabl && tabl[i])
		(tab2[i] = tabl[i]) ? (i++) : 0;
	sec = (struct section_64*)(seg + 1);
	y = -1;
	while (++y < (int)seg->nsects)
		(tab2[i++] = sec->sectname) ? (sec++) : 0;
	free(tabl);
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
	tab2 = (char**)malloc(sizeof(char*) * ((int)seg->nsects + i + 1));
	tab2[seg->nsects + i] = 0;
	i = 0;
	while (tabl && tabl[i])
		(tab2[i] = tabl[i]) ? (i++) : 0;
	sec = (struct section*)(seg + 1);
	y = -1;
	while (++y < (int)seg->nsects)
		(sec++) ? (tab2[i++] = sec->sectname) : 0;
	free(tabl);
	return (tab2);
}

void		handle_64(void *ptr)
{
	int						nb;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	char 					**tabl;

	i = -1;
	header = (struct mach_header_64*)ptr;
	nb = header->ncmds;
	lc = (void*)ptr + sizeof(*header);
	tabl = NULL;
	sym = NULL;
	while (++i < nb)
	{
		if (lc->cmd == LC_SEGMENT_64)
			tabl = get_tab_64(tabl, (struct segment_command_64 *)lc);
		if (lc->cmd == LC_SYMTAB && !sym)
			sym = (struct symtab_command*)lc;
		lc = (void*)lc + lc->cmdsize;
	}
	print_output_64(sym, ptr, tabl);
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
	sym = NULL;
	while (++i < nb)
	{
		if (lc->cmd == LC_SEGMENT)
			tabl = get_tab_32(tabl, (struct segment_command*)lc);
		if (lc->cmd == LC_SYMTAB && !sym)
			sym = (struct symtab_command*)lc;
		lc = (void*)lc + lc->cmdsize;
	}
	print_output_32(sym, ptr, tabl);
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
	else if ((ptr = mmap(0, buf.st_size , PROT_READ, MAP_PRIVATE, fd, 0)) ==
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
