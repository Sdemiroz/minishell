/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:03:12 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/05/02 01:57:59 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_mini(t_minishell *mini)
{
	mini->pipe_list = NULL;
	mini->tokens = NULL;
}

void	main_routine(t_minishell *mini, char *user_input)
{
	if (quotes_error(user_input) == true)
	{
		printf("Error: open quotes don't work!\n");
		mini->exit_code = 1;
		return ;
	}
	else if (parsing(mini, user_input) == false)
	{
		printf("Syntax Error\n");
		mini->exit_code = 2;
		return ;
	}
	if (!mini->pipe_list)
		return ;
	else
		execution(mini);
}

static void	handle_input(t_minishell *mini, char *user_input)
{
	main_routine(mini, user_input);
	if (*user_input)
		add_history(user_input);
	gc_free_local();
	free(user_input);
}

static void	cleanup_shell(void)
{
	printf("exit\n");
	rl_clear_history();
	gc_free_all();
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;
	char		*user_input;

	(void)argc;
	(void)argv;
	gc_init_garbage_collector();
	mini = init_mini(envp);
	if (!mini)
		return (1);
	while (1)
	{
		init_signals();
		reset_mini(mini);
		user_input = readline("bash-3.2$ ");
		if (!user_input)
			break ;
		handle_input(mini, user_input);
	}
	cleanup_shell();
	return (0);
}
