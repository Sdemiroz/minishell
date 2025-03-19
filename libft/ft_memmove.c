/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:42:14 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/10/09 19:58:10 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest_str, const void *src_str, size_t n)
{
	unsigned char		*x;
	const unsigned char	*y;

	x = (unsigned char *)dest_str;
	y = (unsigned char *)src_str;
	if (dest_str == NULL && src_str == NULL)
		return (NULL);
	if (y < x)
	{
		x = x + n - 1;
		y = y + n - 1;
		while (n-- > 0)
			*x-- = *y--;
	}
	else
	{
		while (n-- > 0)
			*x++ = *y++;
	}
	return (dest_str);
}
// int main(void)
//  {
//     char src[] = "Hello, World!";
//     char dest[50]; // Sicherstellen, dass dest groß genug ist
//     size_t n = 5; // Anzahl der Bytes, die kopiert werden sollen

//     printf("Before ft_memmove:\n");
//     printf("Source: %s\n", src);
//     printf("Destination: %s\n", dest);

//     ft_memmove(dest, src, n);
//     dest[n] = '\0';

//     printf("After ft_memmove:\n");
//     printf("Source: %s\n", src);
//     printf("Destination: %s\n", dest); // sollte "Hello" anzeigen

//     return 0;
// }
