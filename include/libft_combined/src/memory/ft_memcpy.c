/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:12:07 by lannur-s          #+#    #+#             */
/*   Updated: 2023/05/19 12:04:49 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*xd;
	const unsigned char	*xs;	

	if (dest == src)
		return (dest);
	xd = dest;
	xs = src;
	while (n--)
		*xd++ = *xs++;
	return (dest);
}
