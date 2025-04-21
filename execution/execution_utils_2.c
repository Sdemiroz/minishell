/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 03:07:30 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/21 04:33:12 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redirection_file(t_redirection *redir)
{
	int	fd;

	if (redir->redirection_type == REDIR_IN)
		fd = open(redir->name_of_file_to_redirect, O_RDONLY);
	else if (redir->redirection_type == REDIR_OUT)
		fd = open(redir->name_of_file_to_redirect, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	else if (redir->redirection_type == REDIR_APPEND)
		fd = open(redir->name_of_file_to_redirect,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (-1);
	return (fd);
}

void	process_fd_redirection(t_redirection *redir, int fd)
{
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
}

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd,
			"env") || !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "unset"));
}

void	execute_command(t_pipe *cmd, t_minishell *mini)
{
	char	*path;
	char	**env_array;

	if (!cmd->cmd || !cmd->cmd[0])
		exit(0);
	path = get_full_path(cmd->cmd[0], mini->env);
	if (!path)
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

int	execute_builtin(char **cmd, t_minishell *mini)
{
	if (!ft_strcmp(cmd[0], "cd"))
		return (ft_cd(cmd, mini));
	else if (!ft_strcmp(cmd[0], "echo"))
		return (ft_echo(cmd, mini));
	else if (!ft_strcmp(cmd[0], "env"))
		return (ft_env(cmd, mini));
	else if (!ft_strcmp(cmd[0], "exit"))
		return (ft_exit(cmd, mini));
	else if (!ft_strcmp(cmd[0], "export"))
		return (ft_export(cmd, mini));
	else if (!ft_strcmp(cmd[0], "unset"))
		return (ft_unset(cmd, mini));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd(cmd, mini));
	return (1);
}
