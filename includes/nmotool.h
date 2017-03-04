/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmotool.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:25:24 by jtranchi          #+#    #+#             */
/*   Updated: 2017/03/04 17:02:50 by jtranchi         ###   ########.fr       */
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
# include "../srcs/libft/includes/libft.h"

typedef struct			s_lt
{
	unsigned long long	value;
	char				*str;
	struct s_lt			*next;
}						t_lt;

void					print_output(struct symtab_command *sym, void *ptr);

#endif
