/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroez <sdemiroez@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:04:08 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/10/10 03:21:05 by sdemiroez        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest_str, const char *src_str, size_t n)
{
	size_t	x;

	x = 0;
	while (src_str[x] != '\0' && x < n - 1)
	{
		if (n != 0)
			dest_str[x] = src_str[x];
		x++;
	}
	if (n != 0)
		dest_str[x] = '\0';
	while (src_str[x] != '\0')
		x++;
	return (x);
}
