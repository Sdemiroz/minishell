/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:09:32 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/21 04:48:14 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	main_cleanup(uint8_t exit_stat)
{
	gc_free_all();
	bzero(get_gc(), sizeof(t_double_gc));
	exit(exit_stat);
}

void	ft_error(char *msg, char *file, int line, uint8_t exit_stat)
{
	fprintf(stderr, "Error: File %s line %d: %s\n", file, line, msg);
	main_cleanup(exit_stat);
}

t_gc_node	*gc_create_node(void *pointer2mem)
{
	t_gc_node	*new_node;

	new_node = (t_gc_node *)malloc(sizeof(t_gc_node) * 1);
	if (!new_node)
		return (NULL);
	new_node->pointer = pointer2mem;
	new_node->next = NULL;
	return (new_node);
}

t_garbage_collector	*gc_init_garbage_collector(void)
{
	t_double_gc	*dgc;

	dgc = get_gc();
	dgc->global.head = NULL;
	dgc->global.tail = NULL;
	dgc->global.size = 0;
	dgc->local.head = NULL;
	dgc->local.tail = NULL;
	dgc->local.size = 0;
	return (&(dgc->global));
}

void	*ft_malloc(size_t size)
{
	return (ft_malloc_local(size));
}
