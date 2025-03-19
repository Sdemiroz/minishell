/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:23:40 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/10/09 19:56:51 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest_str, const void *src_str, size_t n)
{
	unsigned char	*x;
	unsigned char	*y;

	x = (unsigned char *)dest_str;
	y = (unsigned char *)src_str;
	if (dest_str == NULL && src_str == NULL)
		return (NULL);
	while (n-- > 0)
		*x++ = *y++;
	return (dest_str);
}

// int	main(void)
//  {
//     char src[] = "Hello, World!";
//     char dest[50]; // Sicherstellen, dass dest groß genug ist
//     size_t n = 5; // Anzahl der Bytes, die kopiert werden sollen

//     printf("Before ft_memcpy:\n");
//     printf("Source: %s\n", src);
//     printf("Destination: %s\n", dest);

//     ft_memcpy(dest, src, n);
//     dest[n] = '\0';

//     printf("After ft_memcpy:\n");
//     printf("Source: %s\n", src);
//     printf("Destination: %s\n", dest); // sollte "Hello" anzeigen

//     return 0;
// }
