/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:31:46 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/10/15 17:06:42 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void*(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*x;
	t_list	*temp;

	if (!lst || !del || !f)
		return (NULL);
	temp = lst;
	new = NULL;
	while (temp)
	{
		x = malloc(sizeof(t_list));
		if (!x)
		{
			ft_lstclear(&new, del);
			free (x);
			return (NULL);
		}
		x -> content = f(temp -> content);
		x -> next = NULL;
		ft_lstadd_back(&new, x);
		temp = temp -> next;
	}
	free(temp);
	return (new);
}
