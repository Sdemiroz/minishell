/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:03:12 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/11 07:02:24 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_routine(t_minishell *mini, char *user_input)
{
	if (parsing(mini, user_input) == true)
	{
		debug_tokens(mini->tokens);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;
	char		*user_input;

	t_garbage_collector *gc_init_garbage_collector(void);
	(void)argc;
	(void)argv;
	mini = init_mini(envp);
	while (1)
	{
		// MISSING init signals
		user_input = readline("Mini $ ");
		if (!user_input)
			break ;
		if (quotes_error(user_input) == true)
			printf("Error: open quotes dont work!\n");
		if (ft_strcmp(user_input, "exit") == 0)
		{
			free(user_input);
			break;
		}
		else
			main_routine(mini, user_input);
		add_history(user_input);
		free(user_input);
	}
	rl_clear_history();
	gc_free_all();
	return (0);
}

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes
// ./minishell
