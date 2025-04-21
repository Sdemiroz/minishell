/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 08:24:49 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/04/21 06:13:30 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bubble_pass(char **array, int pass, int len)
{
	int		j;
	int		swapped;
	char	*temp;

	j = 0;
	swapped = 0;
	while (j < len - pass - 1)
	{
		if (ft_strcmp(array[j], array[j + 1]) > 0)
		{
			temp = array[j];
			array[j] = array[j + 1];
			array[j + 1] = temp;
			swapped = 1;
		}
		j++;
	}
	return (swapped);
}

void	sort_string_array(char **array)
{
	int	len;
	int	i;

	len = 0;
	while (array[len])
		len++;
	i = 0;
	while (i < len - 1)
	{
		if (!bubble_pass(array, i, len))
			break ;
		i++;
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
			*eq = '=';
		}
		else
			printf("declare -x %s\n", arr[i]);
		i++;
	}
}

void	handle_export_arg(t_minishell *mini, char *arg)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		*eq = '\0';
		key = arg;
		value = eq + 1;
		set_env_value(&mini->env, key, value);
		*eq = '=';
	}
	else
		set_env_value(&mini->env, arg, "");
}

int	ft_export(char **args, t_minishell *mini)
{
	int	i;

	if (!args[1])
	{
		print_export(mini->env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		handle_export_arg(mini, args[i]);
		i++;
	}
	return (0);
}
