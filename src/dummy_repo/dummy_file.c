/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 03:42:22 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/01 03:42:43 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	debug_putstr(char *msg, char *file, const char *function, int line)
{
	ft_putstr(msg);
	ft_putstr(" - FILE: ");
	ft_putstr(file);
	ft_putstr(", FUNCTION: ");
	ft_putstr((char *)function);
	ft_putstr(", LINE: ");
	ft_putstr(ft_itoa(line));
	ft_putstr("\n");
}

void	dummy_file_function(void)
{
	debug_putstr("Fail int o" ,__FILE__, __FUNCTION__, __LINE__);
}
