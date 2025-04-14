/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 03:42:22 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/14 21:01:02 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_parsed_structure(t_pipe_list *pipe_list)
{
	t_pipe *current_pipe;
	t_redirection *current_redir;
	int pipe_count, cmd_index, redir_count;

	if (!pipe_list || !pipe_list->head)
	{
		printf("\n=== EMPTY PARSED STRUCTURE ===\n\n");
		return ;
	}

	printf("\n=== PARSED COMMAND STRUCTURE ===\n");
	current_pipe = pipe_list->head;
	pipe_count = 0;

	while (current_pipe)
	{
		printf("PIPE %d:\n", pipe_count++);

		// Print command and arguments
		printf("  Command: ");
		if (!current_pipe->cmd || !current_pipe->cmd[0])
			printf("(null)");
		else
		{
			cmd_index = 0;
			while (current_pipe->cmd[cmd_index])
			{
				printf("'%s'", current_pipe->cmd[cmd_index]);
				if (current_pipe->cmd[cmd_index + 1])
					printf(" ");
				cmd_index++;
			}
		}
		printf("\n");

		// Print redirections
		if (current_pipe->list_of_redirections
			&& current_pipe->list_of_redirections->head)
		{
			printf("  Redirections:\n");
			current_redir = current_pipe->list_of_redirections->head;
			redir_count = 0;

			while (current_redir)
			{
				printf("    %d. ", redir_count++);

				// Print redirection type
				if (current_redir->redirection_type == REDIR_IN)
					printf("< (input)");
				else if (current_redir->redirection_type == REDIR_OUT)
					printf("> (output)");
				else if (current_redir->redirection_type == REDIR_APPEND)
					printf(">> (append)");
				else if (current_redir->redirection_type == REDIR_HEREDOC)
					printf("<< (heredoc)");

				printf(" -> '%s'\n", current_redir->name_of_file_to_redirect);
				current_redir = current_redir->next;
			}
		}
		else
			printf("  No redirections\n");

		printf("\n");
		current_pipe = current_pipe->next;
	}
	printf("=== END OF PARSED STRUCTURE ===\n\n");
}
