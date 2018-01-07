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

int			print_usage(char **argv)
{
	ft_putstr_fd("usage : ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putendl_fd(" [file]", 2);
	return (EXIT_FAILURE);
}

void		nm(void *ptr)
{
	int magic;

	magic = *(int *)ptr;
	if (magic == (int)MH_MAGIC_64)
		handle_64(ptr);
}

int			myerror(char *str)
{
	ft_putstr("nm : ");
	ft_putstr(str);
	ft_putstr(": error");
	return (EXIT_FAILURE);
}

int			main(int argc, char **argv)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if (argc != 2)
		return (print_usage(argv));
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (myerror("open"));
	if (fstat(fd, &buf) < 0)
		return (myerror("fstat"));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
	MAP_FAILED)
		return (myerror("mmap"));
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		return (myerror("munmap"));
	return (EXIT_SUCCESS);
}
