/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:35:15 by jtranchi          #+#    #+#             */
/*   Updated: 2017/03/03 16:51:24 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

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

void				ft_print_addr(unsigned long long n)
{
	char				str[ft_nbrlen(n)];
	size_t				len;

	len = ft_nbrlen(n) - 1;
	if (n == 0)
	{
		printf("                 ");
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
	printf("0000000%s ",str);
}

void		print_output(struct symtab_command *sym, void *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*array;

	stringtable = (void*)ptr + sym->stroff;
	array = (void*)ptr + sym->symoff;
	i = -1;
	while (++i < sym->nsyms)
	{
		ft_print_addr(array[i].n_value);
		printf("%s\n", stringtable + array[i].n_un.n_strx);
	}
}

void		handle_64(void *ptr)
{
	int		nb;
	int		i;
	struct mach_header_64 *header;
	struct load_command *lc;
	struct symtab_command *sym;

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
	fprintf(stderr, "usage : %s [file]\n", argv[0]);
}


void		nm(void *ptr)
{
	int magic;

	magic = *(int *) ptr;
	if (magic == MH_MAGIC_64)
		handle_64(ptr);
}

int		main(int argc, char **argv)
{
	int				fd;
	char			*ptr;
	struct	stat	buf;

	if (argc != 2)
	{
		print_usage(argv);
		exit(EXIT_FAILURE);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (fstat(fd, &buf) < 0)
	{
		perror("fstat");
		exit(EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}