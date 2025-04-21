/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:09:29 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/21 04:46:12 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	gc_add_global(void *ptr)
{
	if (ptr)
		gc_add_to(&get_gc()->global, ptr);
}

void	gc_add_local(void *ptr)
{
	if (ptr)
		gc_add_to(&get_gc()->local, ptr);
}

void	gc_free_gc(t_garbage_collector *gc)
{
	t_gc_node	*cur;
	t_gc_node	*tmp;

	if (!gc)
		return ;
	cur = gc->head;
	while (cur)
	{
		tmp = cur->next;
		free(cur->pointer);
		free(cur);
		cur = tmp;
	}
	gc->head = NULL;
	gc->size = 0;
}

void	gc_free_all(void)
{
	gc_free_gc(&get_gc()->local);
	gc_free_gc(&get_gc()->global);
}

void	gc_free_local(void)
{
	gc_free_gc(&get_gc()->local);
}
