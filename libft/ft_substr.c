/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:17:48 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/10/11 21:07:15 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	x;
	size_t	y;
	size_t	s_len;
	char	*sub;

	x = 0;
	y = start;
	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (y >= s_len)
		return (ft_strdup(""));
	if (len > s_len - y)
		len = s_len - y;
	sub = (char *)malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	while (x < len && s[y] != '\0')
	{
		sub[x] = s[y];
		x++;
		y++;
	}
	sub[x] = '\0';
	return (sub);
}
