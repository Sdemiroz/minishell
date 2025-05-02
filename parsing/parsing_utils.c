/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:05:38 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/05/02 01:50:28 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	merge_tokens(t_token *curr)
{
	t_token	*next;
	char	*merged_value;

	if (!curr || !curr->next)
		return ;
	next = curr->next;
	if (next->type == WORD && curr->quote_type != NO_QUOTE
		&& !next->start_is_whitespace)
	{
		merged_value = ft_strjoin(curr->value, next->value);
		if (!merged_value)
			return ;
		gc_add_local(merged_value);
		curr->value = merged_value;
		curr->next = next->next;
		merge_tokens(curr);
	}
}

void	add_pipe_to_list(t_pipe_list *list, t_pipe *pipe)
{
	if (!list || !pipe)
		return ;
	if (!list->head)
	{
		list->head = pipe;
		list->tail = pipe;
	}
	else
	{
		list->tail->next = pipe;
		list->tail = pipe;
	}
	list->size_of_list++;
}

t_pipe	*create_pipe(void)
{
	t_pipe	*np;

	np = ft_malloc_local(sizeof(t_pipe));
	if (!np)
		return (NULL);
	np->cmd = NULL;
	np->next = NULL;
	np->list_of_redirections = ft_malloc_local(sizeof(t_redirection_list));
	if (!np->list_of_redirections)
		return (NULL);
	np->list_of_redirections->head = NULL;
	np->list_of_redirections->tail = NULL;
	np->list_of_redirections->size_of_list = 0;
	return (np);
}

void	add_first_word(t_pipe *pipe, char *word)
{
	pipe->cmd = ft_malloc_local(sizeof(char *) * 2);
	if (!pipe->cmd)
		return ;
	pipe->cmd[0] = ft_strdup(word);
	gc_add_local(pipe->cmd[0]);
	pipe->cmd[1] = NULL;
}

void	copy_cmd_array(char **new_cmd, char **cmd, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_cmd[i] = cmd[i];
		i++;
	}
}
