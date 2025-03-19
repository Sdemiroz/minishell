/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:49:15 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/10/10 18:59:16 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const unsigned char	*x;

	x = str;
	while (n-- > 0)
	{
		if (*x == (unsigned char)c)
			return ((void *)x);
		x++;
	}
	return (NULL);
}
