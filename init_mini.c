/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:03:04 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/03/19 00:57:23 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**dup_envp(char **envp, int env_size)
{
	int		i;
	char	**result;

	i = 0;
	result = malloc(sizeof(char *) * (env_size + 1));
	if (!result)
		return(NULL);
	while(envp[i++])
	{
		result[i] = ft_strdup(envp[i]);
		if (!result[i])
		{
			while(--i >= 0)
				free(result[i]);
			free(result);
			return(NULL);
		}
	}
	result[i] = NULL;
	return(result);
}

static int	count_env_entries(char **envp)
{
	int		count;

	count = 0;
	while(envp[count])
		count++;
	return(count);
}

t_minishell	*init_mini(char **envp)
{
	t_minishell 	*mini;
	int				env_size;
	int				i;

	i = 0;
	mini = malloc(sizeof(t_minishell));
	if(!mini)
		return (NULL);
	mini->pipe_list = NULL;
	mini->exit_code = 0;

	env_size = count_env_entries(envp);
	mini->env = dup_envp(envp, env_size);
	if(!mini->env)
	{
		free(mini);
		return(NULL);
	}
	return(mini);
}
