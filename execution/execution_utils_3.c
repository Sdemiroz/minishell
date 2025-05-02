/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 04:31:24 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/05/02 02:55:03 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_io_for_child(t_pipe *cmd, int prev_fd, int *pipe_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (cmd->list_of_redirections)
		handle_redirections(cmd->list_of_redirections->head);
}

void	execute_pipeline(t_minishell *mini, t_pipe *cmd, int prev_fd)
{
	int		pipe_fd[2];
	int		*pipe_ptr;
	pid_t	pid;

	while (cmd)
	{
		prepare_pipes(cmd, pipe_fd, &pipe_ptr);
		pid = fork();
		if (pid == 0)
			child_exec(cmd, prev_fd, pipe_ptr, mini);
		else if (pid < 0)
			return ;
		close_pipe_fds(&prev_fd, pipe_ptr);
		cmd = cmd->next;
	}
}

// Modify process_builtin in execution_utils_3.c
void	process_builtin(t_pipe *cmd, t_minishell *mini)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = -1;
	stdout_backup = -1;
	if (cmd->list_of_redirections && cmd->list_of_redirections->head)
		setup_redirection_with_backup(cmd, &stdin_backup, &stdout_backup);
	mini->exit_code = execute_builtin(cmd->cmd, mini);
	if (stdin_backup != -1 || stdout_backup != -1)
		restore_std_fds(stdin_backup, stdout_backup);
}

void	wait_for_children(t_minishell *mini)
{
	int		status;
	pid_t	last_pid;

	errno = 0;
	last_pid = wait(&status);
	while (last_pid > 0)
	{
		if (WIFEXITED(status))
			mini->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			WTERMSIG(status);
			mini->exit_code = 128 + WTERMSIG(status);
		}
		last_pid = wait(&status);
	}
}

void	prepare_pipes(t_pipe *cmd, int *pipe_fd, int **pipe_ptr)
{
	*pipe_ptr = NULL;
	if (cmd->next && pipe(pipe_fd) == -1)
		return ;
	if (cmd->next)
		*pipe_ptr = pipe_fd;
}
