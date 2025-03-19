/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:26:35 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/11/29 21:55:02 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest_str, const char *src_str, size_t n)
{
	size_t	dn;
	size_t	sn;
	size_t	x;

	dn = ft_strlen(dest_str);
	sn = ft_strlen(src_str);
	x = 0;
	if (n <= dn)
		return (n + sn);
	while (src_str[x] != '\0' && (dn + x) < (n - 1))
	{
		dest_str[dn + x] = src_str[x];
		x++;
	}
	dest_str[dn + x] = '\0';
	return (dn + sn);
}
