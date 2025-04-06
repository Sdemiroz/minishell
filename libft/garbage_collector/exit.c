/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:09:32 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/03/19 01:16:01 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	main_cleanup(uint8_t exit_stat)
{
	gc_free_all();
	bzero(get_gc(), sizeof(t_garbage_collector));
	exit(exit_stat);
}

void	ft_error(char *msg, char *file, int line, uint8_t exit_stat)
{
	fprintf(stderr, "Error: File %s line %d: %s\n", file, line, msg);
	main_cleanup(exit_stat);
}
