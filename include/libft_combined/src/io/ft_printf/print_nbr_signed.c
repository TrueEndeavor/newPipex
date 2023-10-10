/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr_signed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:58:04 by lannur-s          #+#    #+#             */
/*   Updated: 2023/06/21 13:07:20 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_nbr_signed(int n)
{
	int	len;
	int	adjustment;

	len = 0;
	adjustment = 0;
	if (n == INT_MIN)
	{
		n += 1;
		adjustment = 1;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', STD_OUT);
		n = -n;
		len++;
	}
	if (n >= 10)
		len += print_nbr_signed(n / 10);
	ft_putchar_fd(n % 10 + adjustment + '0', STD_OUT);
	len++;
	return (len);
}
