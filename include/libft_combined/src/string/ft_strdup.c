/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:22:17 by lannur-s          #+#    #+#             */
/*   Updated: 2023/05/16 15:24:42 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	char	*dst;
	int		len;

	len = ft_strlen(string);
	dst = (char *)malloc(len + 1 * sizeof(char));
	if (!dst)
		return (0);
	ft_memcpy(dst, string, len);
	dst[len] = '\0';
	return (dst);
}
