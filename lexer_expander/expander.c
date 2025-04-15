/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:12:53 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/15 03:16:19 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *str, char c)
{
	char	*new;
	size_t	len;
	size_t	i;

	i = 0;
	if (!str)
		len = 0;
	else
		len = ft_strlen(str);
	new = ft_malloc_local(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	return (new);
}

int	handle_expansion(char **expanded, char *start, t_env *env, int exit_code)
{
	char	*key;
	char	*value;
	char	*exit_str;
	int		var_len;
	int		skip;

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
		return(2);
	}
	var_len = get_var_len(&start[1]);
	if (var_len == 0)
	{
		if(start[1] && !ft_isalpha(start[1]) && start[1] != '_')
		{
			skip = 2;
			if(!ft_isspace(start[1]))
			{
				while(!ft_isspace(start[skip]) && start[skip] != '$')
					skip++;
			}
			*expanded = ft_strjoin_gc(*expanded, "");
			return(skip);
		}
		else
		{
			*expanded = append_char(*expanded, '$');
			return (1);
		}
	}
	key = ft_substr(&start[1], 0, (size_t)var_len);
	gc_add_local(key);
	value = get_env_value(env, key, var_len);
	*expanded = ft_strjoin_gc(*expanded, value);
	return (var_len + 1);
}

void	ft_expand(t_token *token, t_env *env, int exit_code)
{
	char	*str;
	char	*expanded;
	int		x;

	x = 0;
	expanded = NULL;
	str = token->value;
	while (str[x])
	{
		if (str[x] == '$')
			x += (int)handle_expansion(&expanded, &str[x], env, exit_code);
		else
			expanded = append_char(expanded, str[x++]);
	}
	token->value = expanded;
}

void	expand_tokens(t_token *head_token_list, t_env *env, int exit_code)
{
	t_token	*temp;

	temp = head_token_list;
	if (temp == NULL)
		return ;
	while (temp)
	{
		if (temp->quote_type != SINGLE_QUOTE && strchr(temp->value, '$'))
			ft_expand(temp, env, exit_code);
		temp = temp->next;
	}
}
