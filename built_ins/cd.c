/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 08:23:58 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/19 22:19:33 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **args, t_minishell *mini)
{
	char	*path;
	char	*oldpwd;
	char	cwd[4096];

	oldpwd = getcwd(NULL, 0);
	if (!args[1])
		path = get_env_value(mini->env, "HOME");
	else
		path = args[1];
	if (!path || chdir(path) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	if (oldpwd)
		set_env_value(mini->env, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_value(mini->env, "PWD", cwd);
	free(oldpwd);
	return (0);
}
