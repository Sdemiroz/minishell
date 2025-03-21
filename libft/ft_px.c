/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_px.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:09:29 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/03/19 01:43:42 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nto_str(unsigned long nbr)
{
	char	*xbase;
	int		x;

	xbase = "0123456789abcdef";
	if (nbr >= 16)
	{
		nto_str(nbr / 16);
		nto_str(nbr % 16);
	}
	else
	{
		x = ft_putchar(xbase[nbr]);
		if (x < 0)
			return (-1);
	}
	return (0);
}

int	ft_px(unsigned long nbr)
{
	int			cc;
	int			x;

	cc = 1;
	cc += ft_putstr("0x");
	if (cc != 3)
		return (-1);
	x = nto_str(nbr);
	if (x < 0)
		return (-1);
	while (nbr >= 16)
	{
		nbr /= 16;
		cc++;
	}
	return (cc);
}
