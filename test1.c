/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:27:36 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/03/16 00:28:09 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell *create_example1(void)
{
    t_minishell *minishell = malloc(sizeof(t_minishell));
    t_pipe_list *pipe_list = malloc(sizeof(t_pipe_list));
    t_pipe *pipe = malloc(sizeof(t_pipe));

    // Initialize minishell
    minishell->pipe_list = pipe_list;
    minishell->env = NULL; // Assume env is set elsewhere or hardcoded
    minishell->exit_code = 0;

    // Initialize pipe_list
    pipe_list->head = pipe;
    pipe_list->tail = pipe;
    pipe_list->size_of_list = 1;

    // Initialize pipe (ls -l)
    pipe->list_of_redirections = NULL; // No redirections
    pipe->cmd = malloc(sizeof(char *) * 3); // ls, -l, NULL
    pipe->cmd[0] = "ls";
    pipe->cmd[1] = "-l";
    pipe->cmd[2] = NULL;
    pipe->next = NULL;

    return minishell;
}
