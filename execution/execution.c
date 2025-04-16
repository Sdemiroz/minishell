/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 03:26:04 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/16 06:29:45 by sdemiroz         ###   ########.fr       */
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
		line = readline("> ");
		if (!line)
			break;
		if (ft_strcmp(line, redir->name_of_file_to_redirect) == 0)
		{
			free(line);
			break;
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
			continue;
		}
		if (redir->redirection_type == REDIR_IN)
			fd = open(redir->name_of_file_to_redirect, O_RDONLY);
		else if (redir->redirection_type == REDIR_OUT)
			fd = open(redir->name_of_file_to_redirect, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->redirection_type == REDIR_APPEND)
			fd = open(redir->name_of_file_to_redirect, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
		{
			redir = redir->next;
			continue;
		}
		if (fd == -1)
		{
			perror(redir->name_of_file_to_redirect);
			exit(1);
		}
		if (redir->redirection_type == REDIR_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
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
	handle_redirections(cmd->list_of_redirections ? cmd->list_of_redirections->head : NULL);	if (!cmd->cmd || !cmd->cmd[0])
		exit(0);
	path = get_full_path(cmd->cmd[0], mini->env);
	if (!path)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(cmd->cmd[0], 2);
		exit(127);
	}
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
	pid_t	pid;
	int		status;

	cmd = mini->pipe_list->head;
	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
			return;
		pid = fork();
		if (pid == 0)
			child_exec(cmd, prev_fd, cmd->next ? pipe_fd : NULL, mini);
		else if (pid < 0)
			return;
		close_pipe_fds(&prev_fd, cmd->next ? pipe_fd : NULL);
		cmd = cmd->next;
	}
	while (wait(&status) != -1)
		mini->exit_code = WEXITSTATUS(status);
}
