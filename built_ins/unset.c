/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 08:25:04 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/21 04:10:52 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, t_minishell *mini)
{
	t_env	*curr;
	t_env	*prev;
	int		i;

	i = 1;
	while (args[i])
	{
		curr = mini->env;
		prev = NULL;
		while (curr)
		{
			if (ft_strcmp(curr->key, args[i]) == 0)
			{
				if (prev)
					prev->next = curr->next;
				else
					mini->env = curr->next;
				break ;
			}
			prev = curr;
			curr = curr->next;
		}
		i++;
	}
	return (0);
}
