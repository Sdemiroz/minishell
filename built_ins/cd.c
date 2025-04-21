/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 08:23:58 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/21 04:01:01 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_value(t_env *env, const char *key, const char *value)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			env->value = ft_strdup(value);
			gc_add_global(env->value);
			return ;
		}
		env = env->next;
	}
}

void	add_env_node(t_env **env, const char *key, const char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = ft_malloc_global(sizeof(t_env));
	new_node->key = ft_strdup(key);
	gc_add_global(new_node->key);
	new_node->value = ft_strdup(value);
	gc_add_global(new_node->value);
	new_node->next = NULL;
	if (!*env)
		*env = new_node;
	else
	{
		current = *env;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

void	set_env_value(t_env **env, const char *key, const char *value)
{
	update_env_value(*env, key, value);
	if (!get_env_value(*env, key, (int)ft_strlen(key))[0])
		add_env_node(env, key, value);
}

int	ft_cd(char **args, t_minishell *mini)
{
	char	*path;
	char	*oldpwd;
	char	cwd[4096];

	oldpwd = getcwd(NULL, 0);
	if (!args[1])
		path = get_env_value(mini->env, "HOME", (int)ft_strlen("HOME"));
	else
		path = args[1];
	if (!path || chdir(path) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	if (oldpwd)
		set_env_value(&mini->env, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_value(&mini->env, "PWD", cwd);
	free(oldpwd);
	return (0);
}
