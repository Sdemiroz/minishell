/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:03:04 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/06 15:59:50 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dup_envp(char **envp, int env_size)
{
	int		i;
	char	**result;

	i = 0;
	result = ft_malloc(sizeof(char *) * (size_t)(env_size + 1));
	if (!result)
		return (NULL);
	while (envp[i])
	{
		result[i] = ft_strdup(envp[i]);
		gc_add_begin(result[i]);
		if (!result[i])
		{
			gc_free_all();
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	count_env_entries(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

t_minishell	*init_mini(char **envp)
{
	t_minishell	*mini;
	int			env_size;

	mini = ft_malloc(sizeof(t_minishell));
	if (!mini)
		return (NULL);
	mini->pipe_list = NULL;
	mini->exit_code = 0;
	env_size = count_env_entries(envp);
	mini->env = dup_envp(envp, env_size);
	if (!mini->env)
		return (NULL);
	return (mini);
}

bool	parse_and_init(t_minishell *mini, char *user_input)
{
	//MISSING get_path
	mini->pipe_list = create_tokens(user_input);
}
