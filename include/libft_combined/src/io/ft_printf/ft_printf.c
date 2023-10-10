/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:03:58 by lannur-s          #+#    #+#             */
/*   Updated: 2023/06/21 13:05:46 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_pointer(unsigned long adr)
{
	if (adr)
	{
		print_string("0x");
		return (print_nbr_base(adr, BASE_HEX, LOWER) + 2);
	}
	return (print_string(NIL_STRING));
}

static int	do_print(const char c, va_list args)
{
	if (c == 'c')
		return (print_char(va_arg(args, int)));
	else if (c == 's')
		return (print_string(va_arg(args, char *)));
	else if (c == 'd' || c == 'i')
		return (print_nbr_signed(va_arg(args, int)));
	else if (c == 'u')
		return (print_nbr_base(va_arg(args, unsigned int), BASE_DEC, LOWER));
	else if (c == 'x')
		return (print_nbr_base(va_arg(args, unsigned int), BASE_HEX, LOWER));
	else if (c == 'X')
		return (print_nbr_base(va_arg(args, unsigned int), BASE_HEX, UPPER));
	else if (c == 'p')
		return (print_pointer((unsigned long) va_arg(args, unsigned long)));
	else if (c == '%')
		return (ft_putchar_fd('%', STD_OUT), 1);
	else
		return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		length;

	length = 0;
	va_start(args, format);
	if (!format)
		return (0);
	while (*format != '\0')
	{
		if (*format == '%' && ft_strchr("csdiuxXp%", *(format + 1)) != 0)
		{
			format++;
			length += do_print(*format, args);
		}
		else
		{
			ft_putchar_fd(*format, STD_OUT);
			length++;
		}
		format++;
	}
	va_end(args);
	return (length);
}
