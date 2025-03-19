/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:53:51 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/10/09 18:17:01 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*a;

	a = (unsigned char *)str;
	while (n-- > 0)
		*a++ = (unsigned char)c;
	return (str);
}
// int	main(void)
// {
// 	char str[] = "ABCDEFG";
// 	printf("before : %s\n", str);
// 	ft_memset(str, 'x', 3);
// 	printf("after : %s\n", str);
// }
