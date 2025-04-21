/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:09:01 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/21 04:47:52 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	gc_add_to(t_garbage_collector *gc, void *ptr)
{
	t_gc_node	*new;

	new = gc_create_node(ptr);
	if (!new)
		ft_error("malloc fail", __FILE__, __LINE__, 1);
	new->next = gc->head;
	gc->head = new;
	gc->size++;
}

t_double_gc	*get_gc(void)
{
	static t_double_gc	dgc = {0};

	return (&dgc);
}

void	gc_print_linked_list(t_garbage_collector *gc)
{
	if (!gc)
		return ;
	printf("Len of Linked List: %zu\n", gc->size);
	return ;
}

void	*ft_malloc_global(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_error("malloc fail", __FILE__, __LINE__, 1);
	gc_add_global(ptr);
	return (ptr);
}

void	*ft_malloc_local(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_error("malloc fail", __FILE__, __LINE__, 1);
	gc_add_local(ptr);
	return (ptr);
}
