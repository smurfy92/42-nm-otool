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

#ifndef NM_H
# define NM_H
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/stab.h>
# include <mach-o/fat.h>
# include "../libft/includes/libft.h"

typedef struct			s_lt
{
	unsigned long long	value;
	char				*str;
	uint8_t				type;
	uint8_t				sect;
	struct s_lt			*next;
}						t_lt;

void					print_output_64(struct symtab_command *sym, void *ptr, char **tab);
void					print_output_32(struct symtab_command *sym, void *ptr, char **tab);
void					handle_64(void *ptr);
void					handle_32(void *ptr);
void					ft_find_fat_64(void *ptr);
void					ft_find_fat_32(void *ptr);
void					ft_print_addr(unsigned long long n, int boo);
int						print_usage(char **argv);
void					ft_print_letter(t_lt *lt, char **tab);
int						myerror(char *file, char *str);

#endif
