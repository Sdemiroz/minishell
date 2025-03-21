/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:27:44 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/03/21 07:09:56 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*create_example2(void)
{
	t_minishell	*minishell;
	t_pipe_list	*pipe_list;
	t_pipe		*pipe1;
	t_pipe		*pipe2;

	minishell = malloc(sizeof(t_minishell));
	pipe_list = malloc(sizeof(t_pipe_list));
	pipe1 = malloc(sizeof(t_pipe));
	pipe2 = malloc(sizeof(t_pipe));
	// Initialize minishell
	minishell->pipe_list = pipe_list;
	minishell->env = NULL; // Assume env is set elsewhere
	minishell->exit_code = 0;
	// Initialize pipe_list
	pipe_list->head = pipe1;
	pipe_list->tail = pipe2;
	pipe_list->size_of_list = 2;
	// Pipe 1: ls -l
	pipe1->list_of_redirections = NULL;
	pipe1->cmd = malloc(sizeof(char *) * 3);
	pipe1->cmd[0] = "ls";
	pipe1->cmd[1] = "-l";
	pipe1->cmd[2] = NULL;
	pipe1->next = pipe2;
	// Pipe 2: grep "file"
	pipe2->list_of_redirections = NULL;
	pipe2->cmd = malloc(sizeof(char *) * 3);
	pipe2->cmd[0] = "grep";
	pipe2->cmd[1] = "file"; // Quotes handled by parsing
	pipe2->cmd[2] = NULL;
	pipe2->next = NULL;
	return (minishell);
}
