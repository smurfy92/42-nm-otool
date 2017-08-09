/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 14:16:17 by jtranchi          #+#    #+#             */
/*   Updated: 2017/08/09 15:35:23 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include "../libft/includes/libft.h"

typedef struct			s_lt
{
	unsigned long long	value;
	char				*str;
	uint8_t				type;
	struct s_lt			*next;
}						t_lt;

void					ft_print_addr(unsigned long long n);
void					print_output(struct segment_command_64 *seg, struct mach_header_64 *header);

#endif