/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:29:24 by lannur-s          #+#    #+#             */
/*   Updated: 2023/05/17 14:49:18 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		slen;
	size_t		dlen;
	size_t		count;

	count = 0;
	slen = ft_strlen(src);
	if (!size)
		return (slen);
	dlen = ft_strlen(dst);
	if (size <= dlen)
		return (size + slen);
	while ((dlen + count) < size - 1 && src[count])
	{
		dst[dlen + count] = src[count];
		count++;
	}
	dst[dlen + count] = '\0';
	return (dlen + slen);
}
