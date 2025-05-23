/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 04:58:56 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/05/02 01:50:15 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redirection(t_pipe *pipe, t_token_type type, char *filename)
{
	t_redirection	*new_redir;

	if (!pipe || !filename)
		return ;
	new_redir = ft_malloc_local(sizeof(t_redirection));
	if (!new_redir)
		return ;
	new_redir->redirection_type = type;
	new_redir->name_of_file_to_redirect = ft_strdup(filename);
	gc_add_local(new_redir->name_of_file_to_redirect);
	new_redir->next = NULL;
	if (!pipe->list_of_redirections->head)
	{
		pipe->list_of_redirections->head = new_redir;
		pipe->list_of_redirections->tail = new_redir;
	}
	else
	{
		pipe->list_of_redirections->tail->next = new_redir;
		pipe->list_of_redirections->tail = new_redir;
	}
	pipe->list_of_redirections->size_of_list++;
}

void	add_word_to_cmd(t_pipe *pipe, char *word)
{
	int		x;
	char	**new_cmd;

	if (!pipe || !word)
		return ;
	if (!pipe->cmd)
	{
		add_first_word(pipe, word);
		return ;
	}
	x = 0;
	while (pipe->cmd[x])
		x++;
	new_cmd = ft_malloc_local(sizeof(char *) * (size_t)(x + 2));
	if (!new_cmd)
		return ;
	copy_cmd_array(new_cmd, pipe->cmd, x);
	new_cmd[x] = ft_strdup(word);
	gc_add_local(new_cmd[x]);
	new_cmd[x + 1] = NULL;
	pipe->cmd = new_cmd;
}

void	handle_redirection_token(t_pipe *pipe, t_token **curr)
{
	t_token	*target;

	target = (*curr)->next;
	if (target && target->type == WORD)
		add_redirection(pipe, (*curr)->type, target->value);
	*curr = (*curr)->next;
}

void	parse_tokens_to_pipe_list(t_minishell *mini)
{
	t_token	*curr;
	t_pipe	*current_pipe;

	curr = mini->tokens;
	current_pipe = create_pipe();
	add_pipe_to_list(mini->pipe_list, current_pipe);
	while (curr)
	{
		if (curr->type == PIPE)
		{
			current_pipe = create_pipe();
			add_pipe_to_list(mini->pipe_list, current_pipe);
		}
		else if (curr->type == WORD)
		{
			if (curr->quote_type != NO_QUOTE && curr->next
				&& curr->next->type == WORD
				&& curr->start_is_whitespace == false)
				merge_tokens(curr);
			add_word_to_cmd(current_pipe, curr->value);
		}
		else if (curr->type >= REDIR_IN && curr->type <= REDIR_HEREDOC)
			handle_redirection_token(current_pipe, &curr);
		curr = curr->next;
	}
}

bool	parsing(t_minishell *mini, char *user_input)
{
	mini->tokens = create_tokens(user_input);
	if (!mini->tokens)
		return (true);
	expand_tokens(mini->tokens, mini->env, mini->exit_code);
	if (syntax_error_check(mini->tokens))
		return (false);
	mini->pipe_list = ft_malloc_local(sizeof(t_pipe_list));
	if (!mini->pipe_list)
		return (false);
	mini->pipe_list->head = NULL;
	mini->pipe_list->tail = NULL;
	mini->pipe_list->size_of_list = 0;
	parse_tokens_to_pipe_list(mini);
	return (true);
}
