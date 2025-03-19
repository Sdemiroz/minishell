/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:15:47 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/11/29 22:31:33 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*a;

	a = (unsigned char *)str;
	while (n-- > 0)
		*a++ = 0;
}
// int	main(void)
// {
// 	char str[8] = "ABCDEFG";
// 	printf("before : %s\n", str);
// 	ft_bzero(str, 3);
// 	printf("after : %c", str[1]);
// 	printf("%c", str[2]);
// 	printf("%c", str[3]);
// 	printf("%c", str[4]);
// 	printf("%c", str[5]);
// 	printf("%c", str[6]);
// 	printf("%c", str[7]);
// 	return (0);
// }
