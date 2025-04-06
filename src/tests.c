/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:45:38 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/02 17:44:08 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * quotes_error: Checks if the given user input string has unmatched single or double quotes.
 * Returns true if an open quote is found, false otherwise.
 * Handles nested quotes by toggling quote status only when not inside a conflicting quote type.
 * Treats quotes within other quotes as regular characters.
 */

bool	quotes_error(char *user_input)
{
	int		i;
	bool	single_quote_status;
	bool	double_quote_status;

	i = 0;
	single_quote_status = false;
	double_quote_status = false;
	while(user_input[i])
	{
		if (user_input[i] == '\'')
		{
			if (!double_quote_status)
				single_quote_status = !single_quote_status;
		}
		else if (user_input[i] == '\"')
		{
			if (!single_quote_status)
				double_quote_status = !double_quote_status;
		}
		i++;
	}
	return (single_quote_status || double_quote_status);
}
