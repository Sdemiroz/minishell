/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:06:02 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/10/15 13:28:52 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_numlen(long num)
{
	size_t	dc;

	dc = 1;
	if (num < 0)
		num = -num;
	while (num > 9)
	{
		num = num / 10;
		dc++;
	}
	return (dc);
}

static char	*ft_getchar(long num, size_t len, int sign)
{
	char	*str;

	str = (char *)malloc((len +1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (sign == -1)
	{
		str[0] = '-';
		num = -num;
	}
	while (num != 0)
	{
		str[--len] = (num % 10) + '0';
		num = num / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*res;
	long	num;
	int		sign;
	size_t	len;

	sign = 1;
	num = n;
	len = ft_numlen(num);
	if (n < 0)
	{
		sign = -1;
		len ++;
	}
	res = ft_getchar(num, len, sign);
	return (res);
}
