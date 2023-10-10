/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:00:31 by lannur-s          #+#    #+#             */
/*   Updated: 2023/06/21 13:07:56 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_string(char *s)
{
	if (!s)
	{
		ft_putstr_fd(NULL_STRING, STD_OUT);
		return (6);
	}
	else
	{
		ft_putstr_fd(s, STD_OUT);
		return ((int)ft_strlen(s));
	}
}
