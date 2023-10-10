/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:23:01 by lannur-s          #+#    #+#             */
/*   Updated: 2023/05/23 12:40:17 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char	*little, size_t len)
{
	size_t		little_len;

	if (*little == '\0')
		return ((char *)big);
	else if (len == 0 || *big == '\0')
		return (NULL);
	little_len = ft_strlen(little);
	while (len > 0 && len >= little_len && *big && *little)
	{
		if (ft_strncmp(big, little, little_len) == 0)
			return ((char *)big);
		++big;
		--len;
	}
	return (NULL);
}
