/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:03:12 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/21 01:41:36 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_routine(t_minishell *mini, char *user_input)
{
	if (parsing(mini, user_input) == false)
	{
		printf("Syntax Error\n");
		return ;
	}
	if (!mini->pipe_list)
		return;
	else
		execution(mini);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;
	char		*user_input;

	t_garbage_collector *gc_init_garbage_collector(void);
	(void)argc;
	(void)argv;
	gc_init_garbage_collector();
	mini = init_mini(envp);
	if (!mini)
		return (1);
	while (1)
	{
		init_signals();
		user_input = readline("Minishell Samed $ ");
		if (!user_input)
			break ;
		if (quotes_error(user_input) == true)
			printf("Error: open quotes don't work!\n");
		else if (ft_strcmp(user_input, "exit") == 0)
		{
			free(user_input);
			break ;
		}
		else
			main_routine(mini, user_input);
		add_history(user_input);
		gc_free_local();
		free(user_input);
	}
	rl_clear_history();
	gc_free_all();
	return (0);
}
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell
// ./minishell
