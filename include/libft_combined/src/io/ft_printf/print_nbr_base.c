/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:34:57 by lannur-s          #+#    #+#             */
/*   Updated: 2023/08/01 15:49:44 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_nbr_base(unsigned long nbr, int base, int uppercase)
{
	int				length;

	length = 0;
	if (nbr >= (unsigned int) base)
		length += print_nbr_base(nbr / base, base, uppercase);
	if (nbr % base >= 10)
	{
		if (uppercase == UPPER)
			ft_putchar_fd(((nbr % base) - 10) + 'A', STD_OUT);
		else
			ft_putchar_fd(((nbr % base) - 10) + 'a', STD_OUT);
	}
	else
		ft_putchar_fd((nbr % base) + '0', STD_OUT);
	length++;
	return (length);
}
