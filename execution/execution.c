/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 03:26:04 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/21 04:36:22 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_redirection *redir)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("heredoc pipe");
		exit(1);
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strcmp(line, redir->name_of_file_to_redirect) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
}

void	handle_redirections(t_redirection *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->redirection_type == REDIR_HEREDOC)
		{
			handle_heredoc(redir);
			redir = redir->next;
			continue ;
		}
		fd = open_redirection_file(redir);
		if (fd == -1 && redir->redirection_type != REDIR_IN
			&& redir->redirection_type != REDIR_OUT
			&& redir->redirection_type != REDIR_APPEND)
		{
			redir = redir->next;
			continue ;
		}
		process_fd_redirection(redir, fd);
		redir = redir->next;
	}
}

void	child_exec(t_pipe *cmd, int prev_fd, int *pipe_fd, t_minishell *mini)
{
	setup_io_for_child(cmd, prev_fd, pipe_fd);
	execute_command(cmd, mini);
}

void	close_pipe_fds(int *prev_fd, int *pipe_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (pipe_fd)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

void	execution(t_minishell *mini)
{
	t_pipe	*cmd;
	int		prev_fd;

	cmd = mini->pipe_list->head;
	if (mini->pipe_list->size_of_list == 1 && cmd->cmd
		&& is_builtin(cmd->cmd[0]))
	{
		process_builtin(cmd, mini);
		return ;
	}
	prev_fd = -1;
	execute_pipeline(mini, cmd, prev_fd);
	wait_for_children(mini);
}
