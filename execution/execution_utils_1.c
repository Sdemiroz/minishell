/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:01:16 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/21 04:18:11 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_full_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	paths = get_paths(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin_path(paths[i], cmd);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free_paths(paths);
	return (NULL);
}

char	**env_to_array(t_env *env)
{
	t_env	*current;
	char	**env_array;
	int		count;
	int		i;

	count = 0;
	i = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	env_array = ft_malloc_local(sizeof(char *) * (size_t)(count + 1));
	if (!env_array)
		return (NULL);
	current = env;
	while (current)
	{
		env_array[i++] = ft_strjoin_gc(ft_strjoin_gc(current->key, "="),
				current->value);
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

char	**get_paths(t_env *env)
{
	char	*path_value;
	char	**paths;

	path_value = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			path_value = env->value;
			break ;
		}
		env = env->next;
	}
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	return (paths);
}

char	*ft_strjoin_path(char *path, char *cmd)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(path, "/");
	result = ft_strjoin(tmp, cmd);
	free(tmp);
	return (result);
}

void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}
