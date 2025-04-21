/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:07:52 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/21 04:47:09 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <sys/types.h>

typedef struct s_gc_node
{
	void				*pointer;
	struct s_gc_node	*next;
}						t_gc_node;

typedef struct s_garbage_collector
{
	t_gc_node			*head;
	t_gc_node			*tail;
	size_t				size;
}						t_garbage_collector;

typedef struct s_double_gc
{
	t_garbage_collector	global;
	t_garbage_collector	local;
}						t_double_gc;

void					*ft_malloc(size_t size);
void					*ft_malloc_local(size_t size);
void					*ft_malloc_global(size_t size);
void					gc_add_global(void *ptr);
void					gc_add_local(void *ptr);
void					gc_free_local(void);
void					gc_free_all(void);
void					gc_print_linked_list(t_garbage_collector *gc);
void					gc_add_to(t_garbage_collector *gc, void *ptr);
void					gc_free_gc(t_garbage_collector *gc);
t_gc_node				*gc_create_node(void *ptr);
t_double_gc				*get_gc(void);
void					ft_error(char *msg, char *file, int line,
							uint8_t exit_stat);
void					main_cleanup(uint8_t exit_stat);
t_garbage_collector		*gc_init_garbage_collector(void);

#endif
