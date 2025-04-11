/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 04:58:56 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/11 08:14:46 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parsing(t_minishell *mini, char *user_input)
{
	mini->tokens = create_tokens(user_input);
	expand_tokens(mini->tokens, mini->env, mini->exit_code);
	return(true);
}
