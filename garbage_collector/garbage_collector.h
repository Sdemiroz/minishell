/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:07:52 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/03/21 07:09:13 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>

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

t_gc_node				*gc_create_node(void *pointer2mem);
void					gc_add_begin(void *pointer);
t_garbage_collector		*gc_init_garbage_collector(void);
void					gc_print_linked_list(t_garbage_collector *gc);
void					gc_free_all(void);
t_garbage_collector		*get_gc(void);
void					*ft_malloc(size_t size);
void					main_cleanup(uint8_t exit_stat);
void					ft_error(char *msg, char *file, int line,
							uint8_t exit_stat);

#endif
