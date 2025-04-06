/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:06:35 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/06 18:16:07 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_spaces(char *user_input, int *i, int *start)
{
	while(user_input[*i] && ft_isspace(user_input[*i]))
	{
		*i = *i + 1;
	}
	*start = *i;
}

void	iter_quote(char *user_input, int *i)
{
	char	quote;

	quote = user_input[*i]; //saves the type of quote
	*i = *i + 1; // iterates once to get to an "not quote" char
	while(user_input[*i] && user_input[*i] != quote)
		*i = *i + 1; // skips chars until the same kind of quote is met
	*i = *i + 1;
}
int		is_redirection(char	*user_input)
{
	if (!user_input)
		return(0);
	if (user_input[0] == '<')
	{
		if (user_input[1] == '<')
			return(2);
		return(1);
	}
	if (user_input[0] == '>')
	{
		if (user_input[1] == '>')
			return(2);
		return(1);
	}
}
