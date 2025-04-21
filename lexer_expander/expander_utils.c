/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 03:38:29 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/21 04:43:57 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, const char *key, int var_len)
{
	char	*empty;

	while (env)
	{
		if (ft_strncmp(env->key, key, (size_t)var_len) == 0)
			return (env->value);
		env = env->next;
	}
	empty = ft_strdup("");
	gc_add_local(empty);
	return (empty);
}

char	*ft_strjoin_gc(char *s1, char *s2)
{
	char	*new;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	new = ft_strjoin(s1, s2);
	gc_add_local(new);
	return (new);
}

int	get_var_len(char *str)
{
	int	x;

	x = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[x] && (ft_isalnum(str[x]) || str[x] == '_'))
		x++;
	return (x);
}

int	handle_non_alpha_expansion(char **expanded, char *start)
{
	int	skip;

	skip = 2;
	if (!ft_isspace(start[1]))
	{
		while (!ft_isspace(start[skip]) && start[skip] != '$')
			skip++;
	}
	*expanded = ft_strjoin_gc(*expanded, "");
	return (skip);
}

int	handle_special_expansion(char **expanded, char *start, int exit_code)
{
	char	*exit_str;

	if (start[1] == '?')
	{
		exit_str = ft_itoa(exit_code);
		gc_add_local(exit_str);
		*expanded = ft_strjoin_gc(*expanded, exit_str);
		return (2);
	}
	else if (start[1] == '$')
	{
		*expanded = ft_strjoin_gc(*expanded, "");
		return (2);
	}
	if (start[1] && !ft_isalpha(start[1]) && start[1] != '_')
		return (handle_non_alpha_expansion(expanded, start));
	return (0);
}
