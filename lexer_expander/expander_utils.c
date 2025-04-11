/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 03:38:29 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/11 19:38:22 by sdemiroz         ###   ########.fr       */
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
