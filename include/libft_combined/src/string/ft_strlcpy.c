/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:12:03 by lannur-s          #+#    #+#             */
/*   Updated: 2023/05/17 14:22:08 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	count;

	len = ft_strlen(src);
	if (!size || !src)
		return (len);
	count = 0;
	while (count < size - 1 && *src)
	{
		*dst++ = *src++;
		count++;
	}
	*dst = '\0';
	return (len);
}
