/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:35:15 by jtranchi          #+#    #+#             */
/*   Updated: 2017/02/17 14:52:14 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

void		print_usage(char **argv)
{
	fprintf(stderr, "usage : %s [file]\n", argv[0]);
}


void		nm(void *ptr)
{
	;
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