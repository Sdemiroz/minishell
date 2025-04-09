/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:56:36 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/09 03:19:07 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	skip_spaces(char *user_input, int *i)
{
	while(user_input[*i] && ft_isspace(user_input[*i]))
	{
		(*i)++;
	}
}

void	add_token_to_back(t_token **head_token, t_token *new_token)
{
	t_token	*temp;

	if (!head_token || !new_token) // Safety check for NULL parameters
		return ;
	if (*head_token == NULL)
		*head_token = new_token;
	else
	{
		temp = *head_token;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

t_token	*create_tokens(char *user_input)
{
	t_token	*head_token;
	t_token	*temp_token;
	int		i;

	head_token = NULL;
	temp_token = NULL;
	i = 0;
	skip_spaces(user_input, &i);
	while (user_input[i])
	{
		if (user_input[i] == '\'' || user_input[i] == '\"')
			temp_token = read_quoted_token(user_input, &i);
		else if (user_input[i] == '>' || user_input[i] == '<'
			|| user_input[i] == '|')
			temp_token = read_redirection_token(user_input, &i);
		else
			temp_token = read_word(user_input, &i);
		add_token_to_back(&head_token, temp_token);
		skip_spaces(user_input, &i);
	}
	return (head_token);
}
