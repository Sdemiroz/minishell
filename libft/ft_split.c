/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 01:37:16 by sdemiroez         #+#    #+#             */
/*   Updated: 2025/01/25 03:13:35 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_count(const char *s, char c)
{
	size_t	x;
	size_t	count;

	x = 0;
	count = 0;
	while (s[x] != '\0')
	{
		if (s[x] != c && ((x == 0) || s[x - 1] == c))
			count++;
		x++;
	}
	return (count);
}

static void	ft_free_all(char **res, size_t z)
{
	if (z == 0)
		free(res);
	while (z > 0)
	{
		free(res[z - 1]);
		z--;
	}
	free(res);
}

static char	**ft_real_split(const char *s, char **res, char c, size_t wc)
{
	size_t	z;
	size_t	y;
	size_t	cc;

	z = 0;
	y = 0;
	while (z < wc)
	{
		cc = 0;
		while (s[y] != '\0' && s[y] == c)
			y++;
		while (s[y] != '\0' && s[y] != c)
		{
			cc++;
			y++;
		}
		res[z] = ft_substr(s, y - cc, cc);
		if (res[z] == NULL)
		{
			ft_free_all(res, z);
			return (NULL);
		}
		z++;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	wc;

	if (s == NULL)
		return (NULL);
	wc = (ft_word_count(s, c));
	res = (char **)ft_calloc((sizeof(char *)), wc + 1);
	if (res == NULL)
	{
		free(res);
		return (NULL);
	}
	res = ft_real_split(s, res, c, wc);
	return (res);
}
