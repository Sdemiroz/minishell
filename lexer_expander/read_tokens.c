/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:18:51 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/09 04:12:40 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	delimiter_check(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\0' || c == '|' || c == '<'
		|| c == '>')
		return (true);
	return (false);
}

t_token	*new_token(t_token_type type, t_quote_type qtype, char *value)
{
	t_token	*token;

	token = ft_malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->quote_type = qtype;
	token->value = value;
	token->next = NULL;
	return (token);
}

t_token	*read_quoted_token(char *user_input, int *i)
{
	char			quote_char;
	int				start;
	char			*value;
	t_quote_type	qtype;

	quote_char = user_input[*i]; // set quote to determine delimeter
	if (quote_char == '\'')
		qtype = SINGLE_QUOTE;
	else
		qtype = DOUBLE_QUOTE;
	(*i)++; // skipping quote
	start = *i;
	while (user_input[*i] && user_input[*i] != quote_char)
		(*i)++;
	value = ft_substr(user_input, (unsigned int)start, (size_t)(*i - start));
	gc_add_begin(value);
	(*i)++;
	return (new_token(WORD, qtype, value));
}

t_token	*read_redirection_token(char *user_input, int *i)
{
	char				*value;
	int					token_len;
	t_token_type		rtype;

	token_len = 1;
	if (user_input[*i] == '<' && user_input[*i + 1] == '<')
	{
		rtype = REDIR_HEREDOC;
		token_len = 2;
	}
	else if (user_input[*i] == '<')
		rtype = REDIR_IN;
	else if (user_input[*i] == '>' && user_input[*i + 1] == '>')
	{
		rtype = REDIR_APPEND;
		token_len = 2;
	}
	else if (user_input[*i] == '>')
		rtype = REDIR_OUT;
	else
		rtype = PIPE;
	value = ft_substr(user_input, (unsigned int)*i, (size_t)token_len);
	gc_add_begin(value);
	*i += token_len;
	return (new_token(rtype, NO_QUOTE, value));
}

t_token	*read_word(char *user_input, int *i)
{
	int		start;
	char	*value;

	start = *i;
	while (user_input[*i] && !delimiter_check(user_input[*i]))
		(*i)++;
	value = ft_substr(user_input, (unsigned int)start, (size_t)(*i - start));
	gc_add_begin(value);
	return (new_token(WORD, NO_QUOTE, value));
}
