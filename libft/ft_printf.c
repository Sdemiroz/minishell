/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:51:43 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/11/29 22:22:31 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_percent_base(va_list arg, char x, int cc)
{
	if (x == 'p')
	{
		cc = ft_px(va_arg(arg, unsigned long));
	}
	else if (x == 'u')
	{
		cc = ft_ux(va_arg(arg, unsigned int));
	}
	else if (x == 'x')
	{
		cc = ft_sx(va_arg(arg, unsigned int));
	}
	else if (x == 'X')
	{
		cc = ft_bx(va_arg(arg, unsigned int));
	}
	else if (x == '%')
		cc = ft_putchar('%');
	return (cc);
}

int	ft_percent(va_list arg, char x)
{
	char		*str;
	int			cc;

	cc = 0;
	if (x == 'c')
		cc = ft_putchar(va_arg(arg, int));
	else if (x == 's')
		cc = ft_putstr(va_arg(arg, char *));
	else if (x == 'd' || x == 'i')
	{
		str = ft_itoa_2(va_arg(arg, int));
		if (!str)
			return (-1);
		cc = ft_putstr(str);
		free(str);
	}
	else if (x == 'p' || x == 'u' || x == 'x' || x == 'X' || x == '%')
		cc = ft_percent_base(arg, x, cc);
	else
		return (-1);
	if (cc < 0)
		return (-1);
	else
		return (cc);
}

int	ft_printf(const char *format, ...)
{
	va_list		arg;
	int			temp;
	int			cc;
	size_t		x;

	va_start(arg, format);
	cc = 0;
	x = 0;
	while (format[x])
	{
		if (format[x] == '%')
		{
			temp = ft_percent(arg, format[++x]);
			x++;
		}
		else
		{
			temp = ft_putchar(format[x]);
			x++;
		}
		if (temp < 0)
			return (va_end(arg), -1);
		cc = cc + temp;
	}
	return (va_end(arg), cc);
}

// int	main(void)
// {
// 	char	*y;
// 	y = "abc";
// 	ft_printf("%s\n\n", "My printf:");
// 	ft_printf("%d \n", 5312);
// 	ft_printf("%% \n");
// 	ft_printf("%p \n", y);
// 	ft_printf("%u \n", -10);
// 	ft_printf("%u \n", INT_MAX);
// 	printf("%s\n\n", "Original printf:");
// 	printf("%d \n", 5312);
// 	printf("%% \n");
// 	printf("%p \n", y);
// 	printf("%u \n", -10);
// 	printf("%u \n", INT_MAX);
// 	return (0);
// }
