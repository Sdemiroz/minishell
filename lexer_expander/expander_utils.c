/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 03:38:29 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/11 05:17:02 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return ("");
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new;

	if(!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	new = ft_strjoin(s1, s2);
	gc_add_begin(new);
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
