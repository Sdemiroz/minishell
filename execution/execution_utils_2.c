/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 03:07:30 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/19 06:24:48 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		open_redirection_file(t_redirection *redir)
{
	int fd;

	if (redir->redirection_type == REDIR_IN)
		fd = open(redir->name_of_file_to_redirect, O_RDONLY);
	else if (redir->redirection_type == REDIR_OUT)
		fd = open(redir->name_of_file_to_redirect,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
