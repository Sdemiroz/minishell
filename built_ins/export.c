/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 08:24:49 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/21 04:11:21 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_string_array(char **array)
{
	int		len;
	char	*temp;
	int		swapped;
	int i, j;

	len = 0;
	while (array[len])
		len++;
	for (i = 0; i < len - 1; i++)
	{
		swapped = 0;
		for (j = 0; j < len - i - 1; j++)
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
				swapped = 1;
			}
		}
		if (swapped == 0)
			break ;
	}
}

void	print_export(t_env *env)
{
	char	**arr;
	int		i;
	char	*eq;

	arr = env_to_array(env);
	sort_string_array(arr);
	i = 0;
	while (arr[i])
	{
		eq = ft_strchr(arr[i], '=');
		if (eq)
		{
			*eq = '\0';
			printf("declare -x %s=\"%s\"\n", arr[i], eq + 1);
			*eq = '='; // restore original
		}
		else
			printf("declare -x %s\n", arr[i]);
		i++;
	}
}

int	ft_export(char **args, t_minishell *mini)
{
	int		i;
	char	*key;
	char	*value;
	char	*eq;

	if (!args[1])
	{
		print_export(mini->env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (eq)
		{
			*eq = '\0';
			key = args[i];
			value = eq + 1;
			set_env_value(&mini->env, key, value);
			*eq = '='; // restore in case it's reused
		}
		else
			set_env_value(&mini->env, args[i], ""); // just add empty var
		i++;
	}
	return (0);
}
