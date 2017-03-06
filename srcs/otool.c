/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 15:33:26 by jtranchi          #+#    #+#             */
/*   Updated: 2017/03/06 15:16:01 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nmotool.h"

void		handle_64(void *ptr)
{
	int						nb;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	i = -1;
	header = (struct mach_header_64*)ptr;
	nb = header->ncmds;
	lc = (void*)ptr + sizeof(*header);
	while (++i < nb)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command*)lc;
			print_output(sym, ptr);
			break ;
		}
		lc = (void*)lc + lc->cmdsize;
	}
}

void		print_usage(char **argv)
{
	ft_putstr_fd("usage : ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putendl_fd(" [file]", 2);
	exit(EXIT_FAILURE);
}

void		otool(void *ptr)
{
	int magic;

	magic = *(int *)ptr;
	if (magic == (int)MH_MAGIC_64)
		handle_64(ptr);
}

void		myerror(char *str)
{
	ft_putstr("nm : ");
	ft_putstr(str);
	ft_putstr(": error");
	exit(EXIT_FAILURE);
}

int			main(int argc, char **argv)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if (argc != 2)
		print_usage(argv);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		myerror("open");
	if (fstat(fd, &buf) < 0)
		myerror("fstat");
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		myerror("mmap");
	otool(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		myerror("munmap");
	return (EXIT_SUCCESS);
}