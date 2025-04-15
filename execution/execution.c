/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 03:26:04 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/15 05:18:58 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

static void	child_exec(t_pipe *cmd, int prev_fd, int *pipe_fd, t_minishell *mini)
{
	char	*path;

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
	handle_redirections(cmd->list_of_redirections);
	if (!cmd->cmd || !cmd->cmd[0])
		exit(0);
	path = get_full_path(cmd->cmd[0], mini->env);
	if (!path)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(cmd->cmd[0], 2);
		exit(127);
	}
	execve(path, cmd->cmd, mini->env);
	perror("execve");
	exit(1);
}

static void	close_pipe_fds(int *prev_fd, int *pipe_fd)
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
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;
	int		status;

	cmd = mini->pipe_list->head;
	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid == 0)
			child_exec(cmd, prev_fd, cmd->next ? pipe_fd : NULL, mini);
		else if (pid < 0)
			return (perror("fork"));
		close_pipe_fds(&prev_fd, cmd->next ? pipe_fd : NULL);
		cmd = cmd->next;
	}
	while (wait(&status) != -1)
		mini->exit_code = WEXITSTATUS(status);
}
