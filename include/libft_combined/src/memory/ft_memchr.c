/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:11:56 by lannur-s          #+#    #+#             */
/*   Updated: 2023/05/17 08:00:04 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*xs;
	unsigned char	xc;

	xs = (unsigned char *)s;
	xc = (unsigned char)c;
	while (n--)
	{
		if (*xs == xc)
			return (xs);
		xs++;
	}
	return (NULL);
}
