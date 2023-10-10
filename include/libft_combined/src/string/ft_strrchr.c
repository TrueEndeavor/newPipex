/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:06:33 by lannur-s          #+#    #+#             */
/*   Updated: 2023/05/19 07:56:29 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		len;
	const char	*s_end;

	len = ft_strlen(s);
	if ((unsigned char)c == '\0')
	{
		return ((char *)s + len);
	}	
	s_end = s + len - 1;
	while (s_end >= s)
	{
		if (*s_end == (unsigned char)c)
			return ((char *)s_end);
		s_end--;
	}
	if (s_end < s)
	{
		return (NULL);
	}	
	return ((char *)s_end);
}
