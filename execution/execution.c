/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 03:26:04 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/19 21:02:49 by sdemiroz         ###   ########.fr       */
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

void handle_redirections(t_redirection *redir)
{
	int fd;

	while (redir)
	{
		if (redir->redirection_type == REDIR_HEREDOC)
		{
			handle_heredoc(redir);
			redir = redir->next;
			continue;
		}
		fd = open_redirection_file(redir);
		if (fd == -1 && redir->redirection_type != REDIR_IN &&
			redir->redirection_type != REDIR_OUT &&
			redir->redirection_type != REDIR_APPEND)
		{
			redir = redir->next;
			continue;
		}
		process_fd_redirection(redir, fd);
		redir = redir->next;
	}
}

void	child_exec(t_pipe *cmd, int prev_fd, int *pipe_fd, t_minishell *mini)
{
	char	*path;
	char	**env_array;

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
	if (!cmd->cmd || !cmd->cmd[0])
		exit(0);
	if (!(path = get_full_path(cmd->cmd[0], mini->env)))
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(cmd->cmd[0], 2);
		exit(127);
	}
	if (is_builtin(cmd->cmd[0]))
		exit(execute_builtin(cmd->cmd, mini));
	env_array = env_to_array(mini->env);
	execve(path, cmd->cmd, env_array);
	perror("execve");
	exit(1);
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
	int		pipe_fd[2];
	int		prev_fd;
	int		*pipe_ptr;
	pid_t	pid;
	int		status;

	cmd = mini->pipe_list->head;
	if (mini->pipe_list->size_of_list == 1 && cmd->cmd && is_builtin(cmd->cmd[0]))
	{
		handle_redirections(cmd->list_of_redirections->head);
		mini->exit_code = execute_builtin(cmd->cmd, mini);
		return ;
	}
	prev_fd = -1;
	while (cmd)
	{
		pipe_ptr = NULL;
		if (cmd->next && pipe(pipe_fd) == -1)
			return ;
		if (cmd->next)
			pipe_ptr = pipe_fd;
		if ((pid = fork()) == 0)
			child_exec(cmd, prev_fd, pipe_ptr, mini);
		else if (pid < 0)
			return ;
		close_pipe_fds(&prev_fd, pipe_ptr);
		cmd = cmd->next;
	}
	while (wait(&status) != -1)
		mini->exit_code = WEXITSTATUS(status);
}
