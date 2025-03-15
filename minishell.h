/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:26:37 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/03/16 00:28:17 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>


typedef struct s_minishell
{
	t_pipe_list				*pipe_list;
	char					**env;
	int						exit_code;
}		t_minishell;

typedef struct s_pipe_list
{
	t_pipe					*head;
	t_pipe					*tail;
	int						size_of_list;
}		t_pipe_list;

typedef struct s_pipe
{
	t_redirection_list		*list_of_redirections;
	char					**cmd;
	struct s_pipe			*next;
}		t_pipe;

typedef	struct s_redirection_list
{
	t_redirection			*head;
	t_redirection			*tail;
	int						size_of_list;
}		t_redirection_list;

typedef struct s_redirection
{
	t_redirection_type		redirection_type;
	char					*name_of_file_to_redirect;
	struct s_redirection	*next;
}		t_redirection;

typedef enum e_redirection_type
{
    REDIR_INPUT = 0,  // <
    REDIR_OUTPUT = 1, // >
    REDIR_HEREDOC = 2, // <<
    REDIR_APPEND = 3  // >>
} 		t_redirection_type;



#endif
