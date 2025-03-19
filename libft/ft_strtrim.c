/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:16:22 by sdemiroez         #+#    #+#             */
/*   Updated: 2024/10/15 12:57:34 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_or_no(char c, const char *set)
{
	int	x;

	x = 0;
	while (set[x] != '\0')
	{
		if (c == set[x])
			return (1);
		x++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && set_or_no(s1[start], set))
		start ++;
	while (end > start && set_or_no(s1[end - 1], set))
		end--;
	res = (char *)malloc(end - start + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, &s1[start], end - start + 1);
	return (res);
}

// int main(void)
// {
//     char s1[] = "  !!Hello World!!  ";
//     char set[] = " !";

//     char *trimmed_str = ft_strtrim(s1, set);

//     if (trimmed_str)
//     {
//         printf("Original string: '%s'\n", s1);
//         printf("Set of characters to trim: '%s'\n", set);
//         printf("Trimmed string: '%s'\n", trimmed_str);
//         free(trimmed_str); // Free the allocated memory
//     }
//     else
//     {
//         printf("Memory allocation failed!\n");
//     }

//     return 0;
// }
// // gcc -Wall -Werror -Wextra ft_strtrim.c ft_strlcpy.c ft_strlen.c
