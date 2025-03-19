/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:08:07 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/10/11 21:32:08 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l;
	size_t	ls1;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	l = ls1 + ft_strlen(s2) + 1;
	new_str = malloc(l);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, ls1);
	ft_memcpy(new_str + ls1, s2, l - ls1);
	return (new_str);
}
