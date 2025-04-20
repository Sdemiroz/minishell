/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 08:25:36 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/19 21:04:32 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_env(char **args, t_minishell *mini)
{
	char	**env_arr;
	int		i;

	(void)args;
	env_arr = env_to_array(mini->env);
	if (!env_arr)
		return (1); // return non-zero on error

	i = 0;
	while (env_arr[i])
	{
		printf("%s\n", env_arr[i]);
		i++;
	}
	return (0);
}
