/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:56:36 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/06 18:14:57 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe_list		create_tokens(char *user_input)
{
	t_pipe_list		pipe_list;
	int				i;
	int				start;

	i = 0;
	remove_spaces(user_input, &i, &start);
	while(user_input[i])
	{
		if (ft_isquote(user_input[i]))
			iter_quote(user_input, &i);
		else if (is_redirection(user_input + i))

	}
}
