/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:03:04 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/11 18:43:36 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	node = ft_malloc_global(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	append_env_node(t_env **head, t_env **tail, char **parts)
{
	t_env	*new;

	if (parts[0])
		gc_add_global(parts[0]);
	if (parts[1])
	gc_add_global(parts[1]);

	new = new_env_node(parts[0], parts[1]);
	if (!new)
		return ;
	if (!*head)
		*head = new;
	else
		(*tail)->next = new;
	*tail = new;
}


t_env	*env_from_envp(char **envp)
{
	t_env	*head;
	t_env	*tail;
	char	**parts;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i])
	{
		parts = ft_split(envp[i], '=');
		if (!parts || !parts[0] || !parts[1])
		{
			i++;
			continue ;
		}
		append_env_node(&head, &tail, parts);
		if (parts)
			free(parts);
		i++;
	}
	return (head);
}
t_minishell	*init_mini(char **envp)
{
	t_minishell	*mini;

	mini = ft_malloc_global(sizeof(t_minishell));
	if (!mini)
		return (NULL);
	mini->pipe_list = NULL;
	mini->exit_code = 0;
	mini->env = env_from_envp(envp);
	if (!mini->env)
		ft_error("Mini init failed", __FILE__, __LINE__, 1);
	return (mini);
}
