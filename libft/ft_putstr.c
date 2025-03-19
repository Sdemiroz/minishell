/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:47:16 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/11/29 21:52:43 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *x)
{
	int	i;
	int	y;

	i = 0;
	if (!x)
	{
		y = write (1, "(null)", 6);
		if (y != 6)
			return (-1);
		return (y);
	}
	while (x[i])
	{
		y = write(1, &x[i], 1);
		if (y != 1)
			return (-1);
		i++;
	}
	return (i);
}
