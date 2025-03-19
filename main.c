/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:03:12 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/03/19 01:21:34 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell		*mini;

	(void)argc;
	(void)argv;
	mini = init_mini(envp);
	return(0);
}

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./a.out
