/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 03:42:22 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/11 06:20:24 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_putstr(char *msg, char *file, const char *function, int line)
{
	ft_putstr(msg);
	ft_putstr(" - FILE: ");
	ft_putstr(file);
	ft_putstr(", FUNCTION: ");
	ft_putstr((char *)function);
	ft_putstr(", LINE: ");
	ft_putstr(ft_itoa(line));
	ft_putstr("\n");
}

void	dummy_file_function(void)
{
	debug_putstr("Fail int o", __FILE__, __func__, __LINE__);
}
void	print_token_type(t_token_type type)
{
	char	*type_str;

	if (type == WORD)
		type_str = "WORD";
	else if (type == PIPE)
		type_str = "PIPE";
	else if (type == REDIR_IN)
		type_str = "REDIR_IN";
	else if (type == REDIR_OUT)
		type_str = "REDIR_OUT";
	else if (type == REDIR_APPEND)
		type_str = "REDIR_APPEND";
	else if (type == REDIR_HEREDOC)
		type_str = "REDIR_HEREDOC";
	else
		type_str = "UNKNOWN";
	printf("%-12s", type_str);
}

void	print_quote_type(t_quote_type qtype)
{
	char	*qtype_str;

	if (qtype == NO_QUOTE)
		qtype_str = "NO_QUOTE";
	else if (qtype == SINGLE_QUOTE)
		qtype_str = "SINGLE_QUOTE";
	else if (qtype == DOUBLE_QUOTE)
		qtype_str = "DOUBLE_QUOTE";
	else
		qtype_str = "UNKNOWN";
	printf("%-14s", qtype_str);
}

void	debug_tokens(t_token *tokens)
{
	t_token *current;
	int count;

	current = tokens;
	count = 0;
	printf("\n=== TOKEN LIST ===\n");
	printf("#   %-12s%-14s%s\n", "TYPE", "QUOTE_TYPE", "VALUE");
	printf("------------------------------------------\n");

	while (current)
	{
		printf("%-3d", count++);
		print_token_type(current->type);
		print_quote_type(current->quote_type);
		printf("'%s'\n", current->value);
		current = current->next;
	}
	printf("=== END OF TOKENS ===\n\n");
}
