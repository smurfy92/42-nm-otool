/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 15:33:26 by jtranchi          #+#    #+#             */
/*   Updated: 2017/08/09 17:01:26 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/otool.h"

void		handle_64(struct mach_header_64 *header)
{
	int							nb;
	int							i;
	struct segment_command_64	*segment;

	i = -1;
	nb = header->ncmds;
	segment = (struct segment_command_64 *)(header + 1);
	while (++i < nb)
	{
		if (ft_strcmp(segment->segname, SEG_TEXT) == 0)
		{
			print_output(segment, header);
			break ;
		}
		segment = (struct segment_command_64 *)((char *)segment +
		segment->cmdsize);
	}
}

int			print_usage(char **argv)
{
	ft_putstr_fd("usage : ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putendl_fd(" [file]", 2);
	return (EXIT_FAILURE);
}

void		otool(void *ptr)
{
	int magic;

	magic = *(int *)ptr;
	if (magic == (int)MH_MAGIC_64)
		handle_64((struct mach_header_64 *)ptr);
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
	otool(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		return (myerror("munmap"));
	return (EXIT_SUCCESS);
}
