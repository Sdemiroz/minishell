/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:01:16 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/15 20:01:29 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_full_path(char *cmd, t_env *env)
{
    char **paths;
    char *path;
    int i;

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
