/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:05:38 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/13 19:16:05 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pipe_to_list(t_pipe_list *list, t_pipe *pipe)
{
	if(!list || !pipe)
		return;
	if(!list->head)
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
	t_pipe	*new_pipe;

	new_pipe = ft_malloc_local(sizeof(t_pipe));
	if(!new_pipe)
		return(NULL);
	new_pipe->cmd = NULL;
	new_pipe->next = NULL;
	new_pipe->list_of_redirections = ft_malloc_local(sizeof(t_redirection_list));
	if (!new_pipe->list_of_redirections)
		return(NULL);
	new_pipe->list_of_redirections->head = NULL;
	new_pipe->list_of_redirections->tail = NULL;
	new_pipe->list_of_redirections->size_of_list = 0;
	return(new_pipe);
}
