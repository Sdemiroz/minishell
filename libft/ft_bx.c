/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:23:28 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/11/29 21:53:52 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nto_str(unsigned int nbr)
{
	char	*xbase;
	int		x;

	xbase = "0123456789ABCDEF";
	if (nbr >= 16)
	{
		if (nto_str(nbr / 16) < 0)
			return (-1);
		if (nto_str(nbr % 16) < 0)
			return (-1);
	}
	else
	{
		x = ft_putchar(xbase[nbr]);
		if (x < 0)
			return (-1);
	}
	return (0);
}

int	ft_bx(unsigned int nbr)
{
	int			cc;
	int			x;

	cc = 1;
	if (nbr < 0)
	{
		x = ft_putchar('-');
		if (x < 0)
			return (-1);
		cc += 1;
		nbr = -nbr;
	}
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
