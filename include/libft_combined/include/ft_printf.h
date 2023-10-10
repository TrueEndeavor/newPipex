/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:04:15 by lannur-s          #+#    #+#             */
/*   Updated: 2023/08/01 15:55:51 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include "libft.h"

# define STD_OUT 1
# define BASE_HEX 16
# define BASE_DEC 10
# define UPPER 1
# define LOWER 0
# define NULL_STRING "(null)"
# define NIL_STRING "(nil)"

int		ft_printf(const char *format, ...);
int		print_char(char c);
int		print_string(char *s);
int		print_nbr_signed(int n);
int		print_nbr_base(unsigned long n, int base, int uppercase);

#endif
