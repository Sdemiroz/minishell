/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:03:12 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/03/21 06:56:20 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell		*mini;

	(void)argc;
	(void)argv;
	(void)envp;
	mini = NULL;
	printf("mini address: %p\n", (void *)mini);
	t_garbage_collector *gc_init_garbage_collector(void);
	mini = init_mini(envp);
	gc_free_all();
	return(0);
}

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell
