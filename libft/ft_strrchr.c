/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:26:54 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/10/10 18:35:25 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *src, int c)
{
	int	x;

	x = ft_strlen(src);
	while (x >= 0)
	{
		if (src[x] == (char)c)
			return ((char *)&src[x]);
		x--;
	}
	return (0);
}
