/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:27:50 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/03/16 00:28:02 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell *create_example3(void)
{
    t_minishell *minishell = malloc(sizeof(t_minishell));
    t_pipe_list *pipe_list = malloc(sizeof(t_pipe_list));
    t_pipe *pipe1 = malloc(sizeof(t_pipe));
    t_pipe *pipe2 = malloc(sizeof(t_pipe));
    t_redirection_list *redir_list1 = malloc(sizeof(t_redirection_list));
    t_redirection_list *redir_list2 = malloc(sizeof(t_redirection_list));
    t_redirection *redir1 = malloc(sizeof(t_redirection));
    t_redirection *redir2 = malloc(sizeof(t_redirection));

    // Initialize minishell
    minishell->pipe_list = pipe_list;
    minishell->env = NULL; // Assume env is set elsewhere
    minishell->exit_code = 0;

    // Initialize pipe_list
    pipe_list->head = pipe1;
    pipe_list->tail = pipe2;
    pipe_list->size_of_list = 2;

    // Pipe 1: cat file.txt with input redirection
    pipe1->list_of_redirections = redir_list1;
    pipe1->cmd = malloc(sizeof(char *) * 2);
    pipe1->cmd[0] = "cat";
    pipe1->cmd[1] = NULL; // file.txt handled by redirection
    pipe1->next = pipe2;

    // Redirection list for pipe1: < file.txt
    redir_list1->head = redir1;
    redir_list1->tail = redir1;
    redir_list1->size_of_list = 1;
    redir1->redirection_type = REDIR_INPUT;
    redir1->name_of_file_to_redirect = "file.txt";
    redir1->next = NULL;

    // Pipe 2: grep "test" with output redirection
    pipe2->list_of_redirections = redir_list2;
    pipe2->cmd = malloc(sizeof(char *) * 3);
    pipe2->cmd[0] = "grep";
    pipe2->cmd[1] = "test"; // Quotes handled by parsing
    pipe2->cmd[2] = NULL;
    pipe2->next = NULL;

    // Redirection list for pipe2: > output.txt
    redir_list2->head = redir2;
    redir_list2->tail = redir2;
    redir_list2->size_of_list = 1;
    redir2->redirection_type = REDIR_OUTPUT;
    redir2->name_of_file_to_redirect = "output.txt";
    redir2->next = NULL;

    return minishell;
}
