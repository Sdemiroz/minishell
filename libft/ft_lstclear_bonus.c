/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:31:12 by sdemiroz          #+#    #+#             */
/*   Updated: 2024/10/15 16:05:05 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*x;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		x = (*lst)->next;
		ft_lstdelone((*lst), del);
		(*lst) = x;
	}
	*lst = NULL;
}
