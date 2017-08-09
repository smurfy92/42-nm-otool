/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmotool.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:25:24 by jtranchi          #+#    #+#             */
/*   Updated: 2017/08/09 16:51:48 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NMOTOOL_H
# define NMOTOOL_H
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

void					print_output(struct symtab_command *sym, void *ptr);
void					ft_print_addr(unsigned long long n);

#endif
