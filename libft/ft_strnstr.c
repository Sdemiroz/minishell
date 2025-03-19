/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:40:05 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/10/10 20:12:07 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t n)
{
	size_t	len;

	len = 0;
	while (small[len] != '\0')
		len++;
	if (*small == '\0')
		return ((char *)big);
	while (*big != '\0' && n >= len)
	{
		if (ft_strncmp(big, small, len) == 0)
			return ((char *)big);
		big ++;
		n--;
	}
	return (0);
}
