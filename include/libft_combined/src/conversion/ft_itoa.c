/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:55:37 by lannur-s          #+#    #+#             */
/*   Updated: 2023/05/19 11:44:12 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*new;
	int		n_len;
	int		sign;

	sign = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	n_len = ft_find_len(n);
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	new = malloc(n_len + 1 * sizeof(char));
	if (!new)
		return (NULL);
	new[n_len] = 0;
	while (n_len)
	{
		new[--n_len] = n % 10 + '0';
		n /= 10;
	}
	if (sign)
		new[n_len] = '-';
	return (new);
}
